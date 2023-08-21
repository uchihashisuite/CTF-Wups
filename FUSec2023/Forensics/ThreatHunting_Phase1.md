<h1>Phase 1</h1>

- Với bài này cho chúng ta 1 file máy ảo Win 10 32-bit. Thử mở bằng Virtual Box thì thấy khi login vào có khá nhiều ứng dụng tự động start up

![Screenshot 2023-08-21 213730](https://github.com/hams0thuan/CTF-Wups/assets/100038173/bacd97d0-d54d-44cf-a6fd-9ec57de07fdb)

- Đề bài yêu cầu chúng ta tìm được tên của file mã độc vậy thì chắc chắn nó nằm đâu đó trong các thư mục. Tìm sơ qua trong đống file thì không có gì cả ngoài có 1 bộ <code>Sysinternal Suite</code> ở Desktop. Đây là 1 thư mục tổng hợp các tool do chính Microsoft tạo ra để phục vụ nhiều mục đích khác nhau.
- Theo hint của tác giả cho link này <code>https://attack.mitre.org/techniques</code>. Ở đây có tổng hợp các kĩ thuật tấn công của hacker và tác giả gợi ý chú ý phần <code>Persistence</code>. Phần này sẽ tổng hợp các kĩ thuật mà hacker sử dụng để duy trì cuộc tấn công của mình và trong trường hợp này là che giấu và duy trì con malware. Trong đó có kĩ thuật thực thi cùng với Window <code>https://attack.mitre.org/techniques/T1547/</code>
- Nhớ lại lúc trước có khá nhiều ứng dụng được khởi động ngay khi login vào, vậy thì có khả năng con malware này cũng sẽ thực thi như thế.
- Sử dụng tool <code>Autoruns</code> được cho trong bộ Sysinternal để kiểm tra những ứng dụng hay process nào khởi động cùng Window.
![image](https://github.com/hams0thuan/CTF-Wups/assets/100038173/75d0252f-8f55-4c29-a1b5-8d033edd29c1)

- Có thể thấy có khá nhiều ứng dụng, process và service chạy cùng Window khi khởi động. Tuy nhiên trong đó phát hiện ra 1 service lạ với sai tên đường dẫn.
![image](https://github.com/hams0thuan/CTF-Wups/assets/100038173/5fb1b2bc-ad41-489f-a3cf-943a6872f876)

- Thông thường sẽ có tiến trình là <code>svchost.exe</code> đây là tiến trình hợp lệ của Window tuy nhiên ở đây lại là <code>scvhost.exe</code> nên khả nghi
- Thử check bằng Virus Total
![image](https://github.com/hams0thuan/CTF-Wups/assets/100038173/e89165a0-85d0-49f9-878d-393a3e85c04f)
- Như vậy đây chính xác là mẫu mã độc mà ta cần tìm. Cho vào đúng format flag rồi nộp thôi
