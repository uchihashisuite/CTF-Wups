### Secret Agent
The secret agents share private information through a secret services. We take it from a napped agent, but cannot get its private information without knowing secret id. Wrong trials will punch me!
```
nc 34.143.143.97 8000
```

Attachment: *chal_server.py*
```python
import base64
import json
import os
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from secret import secret_client, flag
import socketserver
import sys

key = os.urandom(16)
iv1 = os.urandom(16)
iv2 = os.urandom(16)

def encrypt(msg):
    aes1 = AES.new(key, AES.MODE_CBC, iv1)
    aes2 = AES.new(key, AES.MODE_CBC, iv2)
    enc = aes2.encrypt(aes1.encrypt(pad(msg, 16)))
    return iv1 + iv2 + enc


def decrypt(msg):
    iv1, iv2, enc = msg[:16], msg[16:32], msg[32:]
    aes1 = AES.new(key, AES.MODE_CBC, iv1)
    aes2 = AES.new(key, AES.MODE_CBC, iv2)
    msg = unpad(aes1.decrypt(aes2.decrypt(enc)), 16)
    return msg


def create_user(requestHandler):
    requestHandler.request.sendall(b'Your client id: ')
    client_id = requestHandler.rfile.readline().rstrip(b'\n').decode()
    if client_id:
        data = {"client_id": client_id, "privileged_granted": False}
    else:
        # Default token
        data = {"client_id": secret_client, "privileged_granted": True}
    token = encrypt(json.dumps(data).encode())
    requestHandler.request.sendall(b"Your token: ")
    requestHandler.request.sendall(base64.b64encode(token) + b'\n')


def login(requestHandler):
    requestHandler.request.sendall(b'Your client id: ')
    client_id = requestHandler.rfile.readline().rstrip(b'\n').decode()
    requestHandler.request.sendall(b'Your token: ')
    raw_token = requestHandler.rfile.readline().rstrip(b'\n')
    try:
        raw_token = decrypt(base64.b64decode(raw_token))
    except:
        requestHandler.request.sendall(b"Failed! Check your token again\n")
        return None

    try:
        data = json.loads(raw_token.decode())
    except:
        requestHandler.request.sendall(b"Failed! Your token is malformed\n")
        return None

    if "client_id" not in data or data["client_id"] != client_id:
        requestHandler.request.sendall(b"Failed! Check your client id again\n")
        return None

    return data


def none_menu(requestHandler):
    requestHandler.request.sendall(b"1. New client\n")
    requestHandler.request.sendall(b"2. Log in\n")
    requestHandler.request.sendall(b"3. Exit\n")

    try:
        requestHandler.request.sendall(b"> ")
        inp = int(requestHandler.rfile.readline().rstrip(b'\n').decode())
    except ValueError:
        requestHandler.request.sendall(b"Invalid choice!\n")
        return None

    if inp == 1:
        create_user(requestHandler)
        return None
    elif inp == 2:
        return login(requestHandler)
    elif inp == 3:
        exit(0)
    else:
        requestHandler.request.sendall(b"Invalid choice!\n")
        return None


def user_menu(user, requestHandler):
    requestHandler.request.sendall(b"1. Show flag\n")
    requestHandler.request.sendall(b"2. Log out\n")
    requestHandler.request.sendall(b"3. Exit\n")

    try:
        requestHandler.request.sendall(b"> ")
        inp = int(requestHandler.rfile.readline().rstrip(b'\n').decode())
    except ValueError:
        requestHandler.request.sendall(b"Invalid choice!\n")
        return None

    if inp == 1:
        if "privileged_granted" in user and user["privileged_granted"]:
            requestHandler.request.sendall(flag + b'\n')
        else:
            requestHandler.request.sendall(b"Insuffcient permissions! Alerts triggered!!!\n")
        return user
    elif inp == 2:
        return None
    elif inp == 3:
        exit(0)
    else:
        requestHandler.request.sendall(b"Invalid choice!\n")
        return None

class RequestHandler(socketserver.StreamRequestHandler):

    def handle(self):
        user = None

        self.request.sendall(b"Super-secure secret sharing service for only privileged users!\n")
        self.request.sendall(b"I dare you to get me!\n")
        self.request.sendall(b"=====================================================\n")

        while True:
            if user:
                user = user_menu(user, self)
            else:
                user = none_menu(self)

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

def main(argv):
    host, port = '0.0.0.0', 8000

    if len(argv) == 2:
        port = int(argv[1])
    elif len(argv) >= 3:
        host, port = argv[1], int(argv[2])

    sys.stderr.write('Listening {}:{}\n'.format(host, port))
    server = ThreadedTCPServer((host, port), RequestHandler)
    server.daemon_threads = True
    server.allow_reuse_address = True
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    server.server_close()


if __name__ == '__main__':
    main(sys.argv)
```

Ở challenge này thì mình có thể tạo tài khoản và được cung cấp token cho tài khoản đó. Sau đó thì có thể thực hiện đăng nhập. Nếu mình có quyền "privileged_granted" thì có thể truy cập được vào mục *show flag* và lấy được flag.

Trước hết thì mình để ý hàm tạo user:
```python
def create_user(requestHandler):
    requestHandler.request.sendall(b'Your client id: ')
    client_id = requestHandler.rfile.readline().rstrip(b'\n').decode()
    if client_id:
        data = {"client_id": client_id, "privileged_granted": False}
    else:
        # Default token
        data = {"client_id": secret_client, "privileged_granted": True}
    token = encrypt(json.dumps(data).encode())
    requestHandler.request.sendall(b"Your token: ")
    requestHandler.request.sendall(base64.b64encode(token) + b'\n')
```
Có thể thấy, token là JSON dạng {"client_id": client_id, "privileged_granted": True} được mã hóa thông qua hàm encrypt và base64. Cũng từ đoạn code, mình thấy rằng có thể dễ dàng lấy được đoạn token của secret_client bằng cách để trống *client_id* khi tạo tài khoản.
```
Super-secure secret sharing service for only privileged users!
I dare you to get me!
=====================================================
1. New client
2. Log in
3. Exit
> 1
Your client id:
Your token: yDb0q2pNaoySGmGrFNNWNWooRRl4soz6/g9oMrcLQBmuO+6LMqJuD5Lqc+OzwCUidMuWixJjkx4Zcexawgfyz64c7DGgXDgizbAtIOtwFGBsN210v6bTPAwI/x/pJGmZ
```
Tuy nhiên thì token này cũng chưa ra ngay được flag vì muốn đăng nhập chúng ta cần phải điền cả *client_id*. Vì vậy mình tiến tới xem xét các hàm liên quan tới mã hóa:
```python
key = os.urandom(16)
iv1 = os.urandom(16)
iv2 = os.urandom(16)

def encrypt(msg):
    aes1 = AES.new(key, AES.MODE_CBC, iv1)
    aes2 = AES.new(key, AES.MODE_CBC, iv2)
    enc = aes2.encrypt(aes1.encrypt(pad(msg, 16)))
    return iv1 + iv2 + enc


def decrypt(msg):
    iv1, iv2, enc = msg[:16], msg[16:32], msg[32:]
    aes1 = AES.new(key, AES.MODE_CBC, iv1)
    aes2 = AES.new(key, AES.MODE_CBC, iv2)
    msg = unpad(aes1.decrypt(aes2.decrypt(enc)), 16)
    return msg
```
Ở đây, hàm encrypt sử dụng 2 lần mã hóa AES_CBC với key, iv1, iv2 được gen ra từ hàm *os.random(16)* ở đầu chương trình. Quá trình mã hóa có thể được minh họa như sau:
```
                  [M_1]             [M_2]             [M_3]
(CBC)               |                 |                 |
                    v                 v                 v 
                  (Enc)             (Enc)             (Enc)
                    |                 |                 |
                    v                 v                 v
[IV1] ----------> (Xor)      .----> (Xor)      .----> (Xor) 
                    |        |        |        |        |
                    v -------.        v -------.        v --- ...
                  [T_1]             [T_2]             [T_3]  
(CBC)               |                 |                 |
                    v                 v                 v 
                  (Enc)             (Enc)             (Enc)
                    |                 |                 |
                    v                 v                 v
[IV2] ----------> (Xor)      .----> (Xor)      .-----> (Xor) 
                    |        |        |        |         |
                    v -------.        v -------.         v --- ...
                  [C_1]             [C_2]              [C_3]
```
Quá trình thám mã:
```
                  [C_1]             [C_2]             [C_3]
(CBC)               |                 |                 |
                    v -------.        v -------.        v --- ...
                  (Dec)      |      (Dec)      |      (Dec)
                    |        |        |        |        |
                    v        |        v        |        v
[IV2] ----------> (Xor)      .----> (Xor)      .----> (Xor)
                    |                 |                 |
                    v                 v                 v
                  [T_1]             [T_2]             [T_3]  
(CBC)               |                 |                 |
                    v -------.        v -------.        v --- ...
                  (Dec)      |      (Dec)      |      (Dec)
                    |        |        |        |        |
                    v        |        v        |        v
[IV1] ----------> (Xor)      .----> (Xor)      .----> (Xor)
                    |                 |                 |
                    v                 v                 v
                  [M_1]             [M_2]             [M_3]
```

Vì là CBC nên ở đây, mình sẽ thực hiện tấn công **Padding Oracle Attack**. Lý thuyết sẽ được dựa trên bài viết [này](https://nsbvc.blogspot.com/2019/01/vua-ngo-ra-su-vi-dieu-cua-padding.html).

Với bài này, phần token trong login chính là nơi chúng ta thực hiện tấn công. Message "Failed! Check your token again\n" sẽ là cơ sở để phát hiện unpadding thành công hay không.

Code: 
```python
from tqdm import tqdm
from pwn import *
from base64 import *

r = remote('34.143.143.97', 8000)

 
def recv_line(x):
    for _ in range(x):
        r.recvline()
 
recv_line(3)
 
recv_line(3)
r.sendline(b"1")
r.send(b"\n")
token = r.recvline()

token = b64decode(token[30:158].decode())
print(token)
print(len(token))
 
true_token = [0] * 80
 
for i in range(64, 16, -16):
    for j in range(0, 16):
        for k in tqdm(range(0, 256)):
            if i == 64 and j == 0 and k == 0:
                continue
            query_token = token[:i-j-17]
            query_token += bytes([token[i-j-17] ^ k])
            for u in range(j):
                query_token += bytes([token[i-j-16+u] ^ true_token[i-j+16+u] ^ (j+1)])
            query_token += token[i-16:i+16]
            recv_line(3)
            r.sendline(b"2")
            r.sendline(b"trungpq")
            r.sendline(b64encode(query_token))
            res = r.recvline()
            if b"Check your token again" not in res:
                true_token[i+15-j] = k ^ (j+1)
                break
        print(bytes(true_token))
 
print(bytes(true_token))

```

Output sau khoảng 10p:
```
b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"client_id": "fAiryTypeAn", "privileged_granted'
```
Đến đây thì mình đã biết được *client_id* là fAiryTypeAn. Thử login với token đã lấy được từ trước, mình ra được flag.
```
Super-secure secret sharing service for only privileged users!
I dare you to get me!
=====================================================
1. New client
2. Log in
3. Exit
> 2
Your client id: fAiryTypeAn
Your token: yDb0q2pNaoySGmGrFNNWNWooRRl4soz6/g9oMrcLQBmuO+6LMqJuD5Lqc+OzwCUidMuWixJjkx4Zcexawgfyz64c7DGgXDgizbAtIOtwFGBsN210v6bTPAwI/x/pJGmZ
1. Show flag
2. Log out
3. Exit
> 1
FUSEC{rewire_for_basic_padding_orarcle_attack_is_fresh_didnt_it???}
```
Flag: FUSEC{rewire_for_basic_padding_orarcle_attack_is_fresh_didnt_it???}
