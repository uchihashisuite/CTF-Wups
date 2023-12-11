# Blind

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/bbce54ef-012b-4cab-b986-7452048514fa)

### 1/Initial reconnaissance:

- Vào website thấy một 2 chức năng login và register

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/d3d20ea9-c034-4336-80df-da25cfe04265)

- Theo kinh nghiệm tôi thử chèn các payload SQLi nhưng đều nhận được một thông báo lỗi từ website

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/06a319fe-976d-4576-a32e-b0aac84fedca)

- Tôi đăng kí một tài khoản ngẫu nhiên

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/700957f5-4bce-47ed-bcee-1eb32ca79d2a)

- Và tôi đã đăng nhập thành công

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/8093a6ee-3941-4c09-a982-a9587f97feec)

- Như thấy trên ảnh khi dăng nhập vào website có thêm 1 chức năng là `Profile` nên tôi thử vào đó và thử tìm cách inject sqli payload

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/2131dae0-5881-4545-a6ae-40649dcb699b)

- Nhưng một lần nữa tôi bị báo lỗi nhưng lần này là lỗi từ server

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/461fc056-4a3e-4431-aead-87ac202cf5ce)

- Tôi đã thử nhiều cách và thấy không hiệu quả cuối cùng tôi đã thử bắt request khi đang cập nhật profile bằng burp suite, theo như đề bài thì nó đang bảo chúng ta cố gắng trở thành giám đốc

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/ccada4de-f6a3-4a5f-a8f0-89ec6f36bd2d)

điều đó làm tôi nghĩ tới giờ mình cần phải thay đổi user lên admin. Tôi liền nhớ ra một lỗ hổng tên [`Mass Assignment`](https://cheatsheetseries.owasp.org/cheatsheets/Mass_Assignment_Cheat_Sheet.html), 
tôi thêm parameter `admin=true ` và gửi request đi.

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/23f10f5f-615e-4312-8b85-dfb323eb1ecc)

- Tôi quay lại dashboard và thấy flag ngay trước mặt mình

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/343acf04-74d1-4c0a-9869-6782626eefc2)




