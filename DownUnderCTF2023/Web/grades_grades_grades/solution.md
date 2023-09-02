- Tạo tkhoan xong sẽ thấy chức năng `Grades`

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/7e85f833-1ba3-4c9e-8a88-132ea0ce20e5)

- Check các request

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/eaa54191-6c88-4fa5-8043-50720020f099)

- Check source thì ta nhận định rằng muốn có thể giải quyết bài này chúng ta cần role teacher `is_teacher`

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/a27e8362-2550-4943-9342-c22efc7cb8a5)

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/debf46dd-be45-4c26-b9b4-11200cd4ede0)

- Và đúng là như vậy khi ta thấy muốn gọi được tới `/grades_flag` bắt buộc tkhoan đăng nhập phải role teacher
  
![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/8bbd385e-097b-4e22-b1d4-ddcb9883b3a0)

- Tới đây có lẽ khá stuck vì làm thế nào để có thể lấy được role thì mình nhớ tới một lỗ hổng mình từng gặp [Mass Assignment](https://cheatsheetseries.owasp.org/cheatsheets/Mass_Assignment_Cheat_Sheet.html).

- Theo document của lỗ hổng trên ta sẽ bắt đầu từ bước sign up
  
![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/8fb2ffbc-f6c5-4548-bbf4-629f881b81e7)

- Thêm parameter `is_teacher=true`

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/78daf821-f43b-476d-9d65-91aa3e91d0aa)


- Ta sẽ lấy token của account mới tạo để thay vào token của student

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/55b04211-751a-4874-a81b-3855f453282a)

- Lúc này ta đã thấy Student Role là Teacher

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/b53bed44-fa9b-4375-bba9-9338062ae860)


- Ở website ta thấy xuấn hiện thêm một chức năng `grading tool`

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/eb6743ae-db08-4b00-b345-c98ae62d8653)

- Vào đó, ta lấy được flag

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/be727170-0cdb-4c41-9cdc-2b7ca92f34ac)

