---
layout: post
title: "重合指数法"
date: 2015-10-29 21:56:03 +0800
comments: true
categories: 
---
###重合指数

假设f0,f1...f25表示AB...Z在x中的概率，共有(n 2)种方法来选择x中的任两个元素。对于每一个i,0<=i<=25,共有(fi 2)种方法使得所选的两个元素皆为i,如下公式  
I(x) = (Efi(fi-1) i=0~25)/n(n-1)
将密文串分为m个长度相等的字串，分别为y1,y2...ym,这样可以以列的形式写出密文，组成一个mx(n/m)的矩阵
如下形式:  

    y1 = y1 ym+1...
    y1 = y2 ym+2...
    .          .    . 
    .          .    . 
    .          .    . 
    y1 = ym y2m..
    
如果m是密钥字的长度，每个I(yi)的值的大小约为0.065;  
如果不是，每个子串yi看起来更为随机，因为他们是通过不同密钥以移位的加密方式获得的。对于一个完全随机的串，其重合指数为：0.038




###重合指数法

    def statis(s):
        res = {chr(i+97):0 for i in range(26)}
    	for i in s:
    		res[i] += 1
    	return res
    
    def func(name,m):
    	cipher = ''
    	with open(name) as f:	
    		cipher = f.read()
    	avg = 0.0
    	t = len(cipher)/m
    	#slip
    	for i in range(m):
    		st = ''
    		for j in range(t):
    			st += cipher[m*j + i]
    		
    		tmp = statis(st)
    				
    		sum = 0			#calc
    		for key in tmp:
    			sum += (tmp[key]-1)*tmp[key]
    		Ic = float(sum)/(float(t)*float(t-1))
    		print Ic
    		avg += Ic
    	print avg/float(m)
    
    
    for i in range(25):
    	raw_input()
    	try:
    		print i
    		func('ciphertext', i)
    	except:
    		pass
