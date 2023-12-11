# INIECTIO  

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/bd483567-f47a-47ba-9de1-0ba4824bf736)

### 1/Initial reconnaissance:

- Vào website thấy một bức ảnh crypto và một dòng text, đây tiếp tục là 1 web static tiếp.
  
![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/3422d87d-782d-4123-8b90-63bf4068dc6c)


- Tuy nhiên sau khi scan không thu được gì, để ý trên url có parameter `name?`

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/37ddde68-1c4c-4659-a210-7b9cfc380d0f)

- Ta sẽ thử bắt đầu với inject một vài câu lệnh như `{ls,-la},|,||` vào đó xem thế nào

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/85e575dd-714b-4684-94b7-e07933510ea4)

- Khi nhận được thông báo trên, tôi nhận ra rằng hệ thống đang filter đầu vào của chúng ta. Tôi đã thêm `'` và `"` để xem có lỗi không và quả nhiên thông báo lỗi đã xuất hiện/

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/b3182935-b9f0-4872-9ba7-9eaff87aadea)

- Lại thấy những gì nhập vào đều được thông báo lại lỗi code php nên tôi sẽ thử một payload sau `";phpinfo();// ` và kết quả nhận được thật bất ngờ

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/c38fdf72-4d45-42e1-9c8b-36e25ecf6cb7)


- Giải thích 1 chút về payload `"` là để đóng tên biến, `phpinfo()` là một hàm có sẵn trong php, `;` để escape lỗi vì nếu k thêm sẽ bị lỗi như trong ảnh, `//` để comment lại đoạn code còn lại.

`"phpinfo();//`

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/481f04ee-b37b-4a7f-80f7-675e8fa0e05a)

### 2/Exploitation:

- Sau khi biết được các hàm trong php có thể hoạt động tôi sẽ bắt đầu bằng các command như system, exec, shell_exec nhưng hình như đã có filter nên xuất hiện thông báo lỗi

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/f99c1cdd-a490-4560-b457-5ca67370ada0)

- Tới đây tôi khá stuck và bắt đầu tìm kiếm các hàm thay thế, tôi nhận ra " (backticks) - cũng tương tự như shell_exec() nên tôi đã thử `uname -a` nhưng `echo` cũng bị filter và print. Tới đây tôi lại searching tiếp để tìm cách `echo` và `print` và sau rất lâu tôi đã tìm được `var_dump()` có thể làm như vậy.
- Payload đầu tiên được xây dựng ``` ";var_dump(`ls -lah`);//  ``` và lần này đã thành công và tìm thấy file flag.php.

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/5f40916b-7775-4909-9114-791d6231b80e)

- Nhưng khi tôi thử payload trên với ``` ";var_dump(`cat flag.php`);// ``` thì lại một lần nữa bị filter.

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/7e527a19-4690-42b2-bc0e-8c63c628ac07)

- Tôi đây tôi thực sự rất bực mình vì liên tục bị filter pressing nhưng sau khi suy nghĩ lại thì tôi tìm ra 1 cách bypass khá đơn giản. Tôi dùng technique adding `\`, giờ đây `cat` của tôi sẽ thành `c\at` từ đó tôi có payload cuối cùng ``` ";var_dump(`c\at flag.php`);// ```

![image](https://github.com/hams0thuan/ASC_Cyber_WarGames_23/assets/93731698/78f00cc4-6064-4606-8f3e-e2c016e317f1)

Cuối cùng tôi cũng tìm được flag :))) đcmm cay vlon!
