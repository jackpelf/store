---  
layout: post  
title: "isg_Cryptobaby"  
date: 2015-10-13 23:39:45 +0800  
comments: true  
categories:   
---  
  
###0x00   
加密进行按131进位，逆向脚本如下  
  
###0x01 sol  
  
	def cal(item):  
		res = ''  
		for i in range(4):  
			print item%131  
			res += chr(int(item%131))  
			item = item/131  
		return res[::-1]  
  
  
  
	g = [0xD50ADE5, 0E302789, 0xED66F1F, 0xCD463FF,0xE0D94DD,0xFA4461F,0xCD91DA2]  
  
	result = ''  
	for j in range(7):  
		result += cal(g[j])  
	print result  

###0x02 misc

DialogBoxParam 
函数功能：该函数根据对话框模板资源创建一个模态的对话框  
int DialogBoxParam（HINSTANCE hInstance，LPCTSTR IpTemplateName,HWND hWndParent， DLGPROC IPDialogFunc,LPARAM dwlnitParam）  
IpTemplateName：标识对话框模板。此参数可以指向一个以NULL结尾的字符串的指针,该字符串指定对话框模扳名，或是指定对话框模板的资源标识符的一个整型值  
IpDialogFunc：指向对话框过程的指针

