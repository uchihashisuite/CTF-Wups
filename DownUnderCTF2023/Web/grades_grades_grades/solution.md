- Tạo tkhoan xong sẽ thấy chức năng `Grades`

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/9a3d933b-f707-4ae9-b5fe-b6aad4cca048)

- Check các request

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/1c2a7448-58d4-40f3-9daa-b1bccb57fa03)

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/17da89df-623c-4e31-bc10-1c3033ff24ad)


- Check source thì ta nhận định rằng muốn có thể giải quyết bài này chúng ta cần role teacher `is_teacher`

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/7a996520-f66a-4de5-808b-7f6cd395b81a)

- Và đúng là như vậy khi ta thấy muốn gọi được tới `/grades_flag` bắt buộc tkhoan đăng nhập phải role teacher
  
![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/56edb723-d551-49dd-8197-168ab37234db)

- Tới đây có lẽ khá stuck vì làm thế nào để có thể lấy được role thì mình nhớ tới một lỗ hổng mình từng gặp [Mass Assignment](https://cheatsheetseries.owasp.org/cheatsheets/Mass_Assignment_Cheat_Sheet.html).

- Theo document của lỗ hổng trên ta sẽ bắt đầu từ bước sign up

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/37071ff9-88c3-4542-92bd-62d95befc532)

- Ta sẽ lấy token của account mới tạo để thay vào token của student

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/f09912b5-c3c5-4adc-896e-da11fd2aebda)

- Lúc này ta đã thấy Student Role là Teacher

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/0336f257-88aa-4f8e-b0ef-7aa522a76e72)

- Ở website ta thấy xuấn hiện thêm một chức năng `grading tool`

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/95e13583-9617-4f17-a1dc-e7996212e8ff)

- Vào đó, ta lấy được flag

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/a1bf0cd7-9616-44fd-aca7-9ad98c21c05d)
