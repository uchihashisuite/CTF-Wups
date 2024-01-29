![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/fca6e624-2c24-4ae7-8ad3-8dd8cc2e73dc)

#### Author: Chi Tran (Twitter: @imspicynoodles) (Discord: iam.chi)
#### Description:

Let’s see what you can do with this vulnerable API GW endpoint

##### Server: 

https://huk5xbypcc.execute-api.ap-southeast-2.amazonaws.com/dev/vulnerable?vulnerable="Welcome to TetCTF!"

#### Material:

AWS Account is not needed for this challenge


## 1.Initial reconnaissance

![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/a79fad2d-63c2-4803-bd0e-72edf34472d0)

- Truy cập vào trang web ta thấy được một API hiển thị `Welcome to TetCTF!`. Với một chút kinh nghiệm làm CTF, mình nghĩ rằng có thể injection -> RCE thông qua parameter `vulnerable`. Nên ban đầu mình thử phép tính `7*7` và thấy kết quả trả về `49` mình nghĩ rằng đây là SSTI trong php hoặc python.

- ![image](https://github.com/jiyuumarinshi/CTF-Wups/assets/93731698/2be74f69-a727-49cf-8df4-939625773590)

- 
