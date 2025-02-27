# brain@#(S

**Category** : Pwn
**Points** : 500

Ever heard brainf*ck ?
I implemented one for you, btw it's only support 1 level of [].\
Try with this `HelloWorld` program
```
Input RAM ammount(blocks)?
1000
Input block size(bytes)?
1
Input code size(bytes)?
1000
Input brainf*** code 1000 bytes?
>++++++++[<+++++++++>-]<.>++++[<+++++++>-]<+.+++++++..+++.>>++++++[<+++++++>-]<++.------------.>++++++[<+++++++++>-]<+.<.+++.------.--------.>>>++++[<++++++++>-]<+.
```

nc challenge.fuctf.com 8005

## Files : 
 - [brainf](./brainf)
 - [brainf.c](./brainf.c)
 - [libc.so.6](./libc.so.6)


