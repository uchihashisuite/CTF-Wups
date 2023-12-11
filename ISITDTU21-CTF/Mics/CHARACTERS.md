# ISITDTU21-CTF
CHARACTERS-Misc

![image](https://user-images.githubusercontent.com/93731698/143735366-c6de1cb0-0734-4a7a-b011-91a189cb6687.png)

Giải nén file winrar mà người ta cho và đi tìm sự thật...

![image](https://user-images.githubusercontent.com/93731698/143735383-78a3d29e-bd09-49e5-aab3-5e6bea45e164.png)

Chúng ta nhận được 1 file txt và rar, file rar không mở được ra có password

![image](https://user-images.githubusercontent.com/93731698/143735435-f754d39d-38e0-414d-b10c-1d2a736d2e5d.png)

Trong file txt chúng ta có 1 loạt các từ ak ak pika pipi ka ka pikachu và hint này mình vẫn chưa hiểu để làm gì 

![image](https://user-images.githubusercontent.com/93731698/143735510-01acc780-c6ea-4eb2-9b95-7856f284763f.png)

Sử dụng thủ thuật trong máy tính như trên mà mình đã vào được bên trong file Hex_Base nhưng thực chất chưa mở được khóa

![image](https://user-images.githubusercontent.com/93731698/143735532-88d50dce-a2a0-401f-823b-e27544f8b3dc.png)

Đây là bên trong nó...

![image](https://user-images.githubusercontent.com/93731698/143735546-960a10d6-c572-41df-9c09-bf2893170855.png)

Dãy kí tự số này đã làm mình nghi ngờ, và vì đề bảo bảo Hex_Base nên mình đã đi decrypt các dãy đó ( https://www.convertstring.com/vi/EncodeDecode/HexDecode)

Sau khi giải mã dãy số kí tự trên mình được cái này: Format the flag by character: 7{7_2_10}
Mình đã liên tưởng đến đây có thể là password của cái Hex_Base và đã đúng nó là: 77210
Giải nén xong chúng ta sẽ có file Player.txt 
![image](https://user-images.githubusercontent.com/93731698/143735723-ead1f47e-7799-4f0a-bd91-728b475f5a3a.png)

Và bên trong đó có rất nhiều kí tự kì lạ, mình đã nghĩ ngay tới việc đem nó đi decrypt base64 (Thật ra biết làm gì có chuyện mang lại xài Hex để decrypt nó)
(https://www.base64decode.org/)
Và chúng ta có một list cầu thủ toàn các siêu sao... 
![image](https://user-images.githubusercontent.com/93731698/143735842-cc96fc5d-7b9d-4019-8c32-a353f8b3f2a5.png)

Đến đây khá là mù mịt vì mình không biết phải bắt đầu từ đâu nữa :v mình đã thử rất nhiều flag dưới dạng format 7{7_2_10}. Và rồi mình nhận ra đây là lúc sử dụng cái file Go find the flag.txt ban đầu. Và mình đã thấy ý nó bảo hãy nhìn tới các kí tự cuối của mỗi cái tên cầu thủ ( Đồng thời trước đó mình cũng nghi ngờ vì tổng kí tự cần của flag là 26 và cũng có 26 cầu thủ). Cuối cùng cũng đã có flag đó là " isitdtu{nothing_is_impossible} "



