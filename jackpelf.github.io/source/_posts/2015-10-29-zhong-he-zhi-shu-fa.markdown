---
layout: post
title: "重合指数法"
date: 2015-10-29 21:56:03 +0800
comments: true
categories: 
---

重合指数法

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
