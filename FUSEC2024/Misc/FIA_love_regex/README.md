# FIA love regex

**Category** : Misc
**Points** : 500

Một người nào đó trong FIA vừa đẹp vừa có chiều sâu đi tìm kho báu của Trương Mỹ Lan tắt báo thức 5 ngày 5 đêm ngủ một phát qua hết deadlines để thật tỉnh táo đọc regex.

Flag là chuỗi thỏa mãn regex sau.

> ^FUSec\{(?<=(?=.{53}(?!.)).(?=.{44}nisu).(?=.{23}fia).{4})(?=.{4}(.).{11}\1)(?=.{4}(.).{6}\2)(?=.{6}(.).{27}\3)(?=.{35}(.)\4)(?=.{9}(.).{3}\5)(?=.{15}(.).{10}\6)(?=.{7}(.).{36}\7)(?=.{18}(.).{6}\8)(?=.{16}(.).{7}\9)(?=.{29}(.).{3}\10)(?=(.).{8}\11)(?=.{8}(.).{19}\12)(?=.{37}(.).{4}\13)(?=.{27}(.).{3}\14)(?=.{10}(.).{34}\15)(?=.{11}(.).{11}\16)(?=.{2}(.).{31}\17)(?=.{14}(.).{10}\18)(?=.{38}(.).{4}\19)(?=.{3}(.).{13}\20)(?=.{5}(.).{20}\21)(?=.{10}(.).{11}\22)(?=.{36}(.)\23)(?=.{12}(.).{31}\24)(?=.{15}(.).\25)(?=.(.).{32}\26)(?=.{28}(.).{15}\27)(?=.{30}(.).{14}\28)(?=.{29}(.).{2}\29)(?=.{16}(.).{8}\30)(?=.{26}(.).{17}\31)(?=.{22}(.).{17}\32)(?=.{18}(.).{2}\33)(?=.{20}(.).{7}\34)(?=.(.).{17}\35)(?=.{13}(.).{20}\36)(?=.{31}(.).\37)(?=.{32}(.).{8}\38)(?=.{39}(.).{3}\39).*}$

Flag format: FUSec{...}