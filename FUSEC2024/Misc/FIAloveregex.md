
## FIA love regex

![image](https://github.com/thangpv25/CTF-Wups/assets/93731698/ed3a4b08-3423-42da-8fa1-ae52ca4b750e)

```python
^FUSec\{(?<=(?=.{53}(?!.)).(?=.{44}nisu).(?=.{23}fia).{4})(?=.{4}(.).{11}\1)(?=.{4}(.).{6}\2)(?=.{6}(.).{27}\3)(?=.{35}(.)\4)(?=.{9}(.).{3}\5)(?=.{15}(.).{10}\6)(?=.{7}(.).{36}\7)(?=.{18}(.).{6}\8)(?=.{16}(.).{7}\9)(?=.{29}(.).{3}\10)(?=(.).{8}\11)(?=.{8}(.).{19}\12)(?=.{37}(.).{4}\13)(?=.{27}(.).{3}\14)(?=.{10}(.).{34}\15)(?=.{11}(.).{11}\16)(?=.{2}(.).{31}\17)(?=.{14}(.).{10}\18)(?=.{38}(.).{4}\19)(?=.{3}(.).{13}\20)(?=.{5}(.).{20}\21)(?=.{10}(.).{11}\22)(?=.{36}(.)\23)(?=.{12}(.).{31}\24)(?=.{15}(.).\25)(?=.(.).{32}\26)(?=.{28}(.).{15}\27)(?=.{30}(.).{14}\28)(?=.{29}(.).{2}\29)(?=.{16}(.).{8}\30)(?=.{26}(.).{17}\31)(?=.{22}(.).{17}\32)(?=.{18}(.).{2}\33)(?=.{20}(.).{7}\34)(?=.(.).{17}\35)(?=.{13}(.).{20}\36)(?=.{31}(.).\37)(?=.{32}(.).{8}\38)(?=.{39}(.).{3}\39).*}$
```

### Objective

- Luyện kiến thức về regular expression

### Difficulty

`easy`

### Flag

`FUSec{fffiaifiifiaifaiaiafiaiaaaisisisssfuuunnisunii}`

## Solved

Để làm bài này ta sẽ cần một công cụ để debug regex, làm từng bước để tìm ra chuỗi thỏa mãn. [link](https://regex101.com/)

Ta break nhỏ từng phần của regex ra cho dễ nhìn:
```
^FUSec\{(?<=(?=.{53}(?!.)).(?=.{44}nisu).(?=.{23}fia).{4})
(?=.{4}(.).{11}\1)
(?=.{4}(.).{6}\2)
(?=.{6}(.).{27}\3)
(?=.{35}(.)\4)
(?=.{9}(.).{3}\5)
(?=.{15}(.).{10}\6)
(?=.{7}(.).{36}\7)
(?=.{18}(.).{6}\8)
(?=.{16}(.).{7}\9)
(?=.{29}(.).{3}\10)
(?=(.).{8}\11)
(?=.{8}(.).{19}\12)
(?=.{37}(.).{4}\13)
(?=.{27}(.).{3}\14)
(?=.{10}(.).{34}\15)
(?=.{11}(.).{11}\16)
(?=.{2}(.).{31}\17)
(?=.{14}(.).{10}\18)
(?=.{38}(.).{4}\19)
(?=.{3}(.).{13}\20)
(?=.{5}(.).{20}\21)
(?=.{10}(.).{11}\22)
(?=.{36}(.)\23)
(?=.{12}(.).{31}\24)
(?=.{15}(.).\25)
(?=.(.).{32}\26)
(?=.{28}(.).{15}\27)
(?=.{30}(.).{14}\28)
(?=.{29}(.).{2}\29)
(?=.{16}(.).{8}\30)
(?=.{26}(.).{17}\31)
(?=.{22}(.).{17}\32)
(?=.{18}(.).{2}\33)
(?=.{20}(.).{7}\34)
(?=.(.).{17}\35)
(?=.{13}(.).{20}\36)
(?=.{31}(.).\37)
(?=.{32}(.).{8}\38)
(?=.{39}(.).{3}\39)
.*}$
```

Ta sẽ giải nghĩa từng phần một để thấu hiểu đoạn regex trên. Tham khảo [cheatsheet](https://www.rexegg.com/regex-quickstart.html). Ở bài này kỹ thuật chủ yếu dùng là `Lookarounds`.

- `^FUSec\{`: bắt đầu bằng chuỗi "FUSec{"

- `(?=.{53}(?!.)).`: lấy đúng duy nhất 1 ký tự khi đã đếm đủ 53 ký tự tính từ phải sang, ngoài ra không lấy bất kỳ ký tự nào khác.

![image](https://hackmd.io/_uploads/HyuBAX8QR.png)

- `(?=.{44}nisu).`: lấy 1 ký tự tiếp theo mà tính từ ký tự đó, 44 ký tự sau được tiếp nối bởi chuỗi "nisu"

![image](https://hackmd.io/_uploads/HJ3ByEUQC.png)

- `(?=.{23}fia).{4}`: lấy 4 ký tự tiếp theo mà tính từ ký tự đầu tiên, 23 ký tự sau được tiếp nối bởi chuỗi "fia"

![image](https://hackmd.io/_uploads/r1N4g4IQC.png)

- Cộng thêm `}$` chuỗi sẽ kết thúc bằng "}"

Sau dòng đầu tiên chuỗi matched là "FUSEC{" trong điều kiện chuỗi dưới đây:
`FUSec{qqqqqqqqqqqqqqqqqqqfiaqqqqqqqqqqqqqqqqqnisuqqq}`

![image](https://hackmd.io/_uploads/B1TugVUQ0.png)

- Với `?<=` (`positive lookbehind`), những regex sau đó sẽ được tìm sau chuỗi "FUSec{" có nghĩa là từ khúc sau là điều kiện để thỏa mãn ruột của flag `qqqqqqqqqqqqqqqqqqqfiaqqqqqqqqqqqqqqqqqnisuqqq`.

- `(?=.{4}(.).{11}\1)`: sau 4 ký tự đầu tiên, ký tự thứ 5 sẽ được nhóm vào `group 1`, tiếp tục sau đó 11 ký tự thì ký tự kế tiếp sẽ phải giống với ký tự trong `group 1`. Nghĩa là ký tự thứ 5 phải giống với ký tự thứ 17.

![image](https://hackmd.io/_uploads/ryFtZ4Im0.png)

- `(?=.{4}(.).{6}\2)`: sau 4 ký tự đầu tiên, ký tự thứ 5 sẽ được nhóm vào `group 2`, tiếp tục sau đó 6 ký tự thì ký tự kế tiếp sẽ phải giống với ký tự trong `group 2`. Nghĩa là ký tự thứ 5 phải giống với ký tự thứ 12.

![image](https://hackmd.io/_uploads/Bkl_f4L7C.png)

- `(?=.{6}(.).{27}\3)`: sau 6 ký tự đầu tiên, ký tự thứ 7 sẽ được nhóm vào `group 3`, tiếp tục sau đó 27 ký tự thì ký tự kế tiếp sẽ phải giống với ký tự trong `group 3`. Nghĩa là ký tự thứ 7 phải gioogns với ký tự thứ 35.

![image](https://hackmd.io/_uploads/SkqJEEU70.png)

- Tiếp tục với logic trên xét hết các mệnh đề còn lại thì ta sẽ ra flag thỏa mãn toàn bộ regex.
