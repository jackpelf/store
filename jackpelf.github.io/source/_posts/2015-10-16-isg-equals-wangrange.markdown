---  
layout: post  
title: "isg=wangrange"  
date: 2015-10-16 21:15:00 +0800  
comments: true  
categories:   
---  
###0x00 分析  
  
从第二个空格开始    
  
第一个字符表示操作符,遇到空格count加一，接着执行运算    
  
  
第一个分割，result为最后一个字符-'A'+十倍的result    
  
以后每个分割：先res_1乘以10，在加上字符-'A'    
  
遇到空格则把res赋值res_1的运算    
  
  
总结：即运算符与一个十进制数运算，并继续下去  
  
###0x01 解决方法  
测试开头的几个字母是否是ISG{,其中'{'不可以，就使用最后一个'}',得到key放入x32dbg后弹出flag  
  
###0x02 sol  
  
	from binascii import *  
	from pwn import *  
	import os  
	  
	f = open('wangrange.exe', 'r')  
	d = f.read(12999)  
	data = d[0x15B4:0x1e81]  
	lines = []  
	for i in data.split('\x20\0'):  
		line = i.replace("\0", '').strip()  
		lines.append(line)  
	  
	  
	  
	key = []  
	pre = 'ISG{'  
	for k in range(3):  
		for i in range(256):  
			t = ''  
			for j in str(i):  
				t += chr(ord(j)+17)  
			tmp = t + ' P' + lines[k]  
			tmp1 = ''  
			for j in tmp:  
				if j in 'PMVUX ':  
					tmp1 += j  
				else:  
					tmp1 += str(ord(j) - 65)  
			count = 0  
			for j in tmp1:  
				if j == ' ':  
					count += 1  
			tmp1 = tmp1.replace('P', ')+')  
			tmp1 = tmp1.replace('M', ')-')  
			tmp1 = tmp1.replace('U', ')*')  
			tmp1 = tmp1.replace('V', ')/')  
			tmp1 = tmp1.replace('X', ')^')  
			tmp1 = '('*count + tmp1  
			c = eval(tmp1)  
			c = chr(c%256)  
			if c == pre[k]:  
				key.append(hex(i))  
	  
	for i in range(256):  
		t = ''  
		for j in str(i):  
			t += chr(ord(j)+17)  
		tmp = t + ' P' + lines[31]  
		tmp1 = ''  
		for j in tmp:  
			if j in 'PMVUX ':  
				tmp1 += j  
			else:  
				tmp1 += str(ord(j) - 65)  
		count = 0  
		for j in tmp1:  
			if j == ' ':  
				count += 1  
		tmp1 = tmp1.replace('P', ')+')  
		tmp1 = tmp1.replace('M', ')-')  
		tmp1 = tmp1.replace('U', ')*')  
		tmp1 = tmp1.replace('V', ')/')  
		tmp1 = tmp1.replace('X', ')^')  
		tmp1 = '('*count + tmp1  
		c = eval(tmp1)  
		c = chr(c%256)  
		if c == '}':  
			key.append(hex(i))  
	print key  
  
###0x03 misc  
  
乘法运算级高于位移运算级  
x32dbg  
dump指定内存  
x32dbg	断点  
bpk   
