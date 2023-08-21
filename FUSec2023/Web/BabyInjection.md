# Bayby Injection

### Link: https://baby-inject.fptunisecathon2023.tech/

### Initial reconnaissance:

- Website cho một nơi để nhập và submit thì sẽ trả về các thông tin vừa điền.

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/9ca20af1-c9b3-4501-8d7d-eb4eb6afeaa5)

### Exploitation:

- Ngay từ đầu mình đã đoán thử thách này có thể là Command Injection, SQL Injection, SSTI,... vì theo đề bài `Baby Injection` đã cho hint ngay rồi. Và không mất quá nhiều thời gian, mình thử `{{7*7}}` submit đi thì ra `49`. Nhưng SSTI được chia thành nhiều loại template engine khác nhau tùy thuộc vào ngôn ngữ website sử dụng Python Flask, Django, PHP, NodeJS, Ruby...Kết hợp với wappalzyer dectect được webstie dùng ngôn ngữ PHP. Từ đó mình giảm scope xuống thành 3 template engie có trong PHP là `Twig`, `Smarty` và `Plates`. Sau một hồi research và thử dectect tiếp thì mình khẳng định đó là `Twig`.
  
 ![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/0f09f963-14c6-42bb-9c2a-1c009ec08bd0)
 

- Mình thử payload `{_self}` thành công nhưng khi thử `{_self.env}` website trả về thông báo lỗi khả năng đã filter variable `env` hoặc `.` nên mình đã tìm cách xây dựng payload kiểu khác.

 ![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/4829b385-30a0-41e3-866a-72aef6a036cc)

- Mình thử inject một biểu thức `{{['id',1]}}` và nhập được response của website là `Array`.

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/1f154855-7004-4cfd-a822-bd1168703ee1)

- Tiếp tới mình thử 1 payload trong [hacktricks](https://book.hacktricks.xyz/pentesting-web/ssti-server-side-template-injection#twig-php) `{{['id']|filter('system')}}` nhưng server thông báo lỗi nghĩa là function filter không thể sử dụng, mình search thêm các function có thể dùng trong 1 biểu thức gồm có `map`. `reduce`, `sort`, `dump`,...Và nhận thấy trong payload all of the [things](https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/Server%20Side%20Template%20Injection/README.md#twig) có một payload đúng ý với mình
- Payload: `{{['id',1]|sort('system')|join}}`

 ![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/57786299-9b87-43e2-9b52-39230047b0d0)

- Với việc payload trên đã hoạt động thành công RCE lên server ta tiếp tục thực hiện các tìm flag với payload `{{['ls',1]|sort('system')|join}}`

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/7fbbdf71-619b-4b50-9431-982cddd01889)

- Payload cuối cùng để ra tìm được ems 🍑 `{{['cat flag.txt',1]|sort('system')|join}}`

![image](https://github.com/hams0thuan/CTF-Wups/assets/93731698/26cc3a90-1f35-45a4-a101-d7d502801ec9)

## GGHFDD 🤜✋
