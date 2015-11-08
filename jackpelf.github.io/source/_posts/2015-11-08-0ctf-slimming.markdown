---
layout: post
title: "0ctf-slimming"
date: 2015-11-08 23:36:59 +0800
comments: true
categories: 
---

###0x00 background    
gcc amd64传参    
%rdi，%rsi，%rdx，%rcx，%r8，%r9 用作函数参数
gcc使用rep ret优化分支预测功能
-I 选项可以向GCC的头文件搜索路径中添加新的目录
-L选项向GCC的库文件搜索路径中添加新的目录
source命令的作用就是用来执行一个脚本

###0x01 sol

    import os
    
    def check(s, data):
        f = open('test', 'w')
    	f.write(s)
    	f.close()
    	os.popen('./slimming test testdata')
    	f = open('testdata', 'r')
    	ss = f.read()
    	f.close()
    	if(cmp(ss, data[:len(ss)]) == 0):
    		return True
    	return False
    
    data_file = 'slimming_data'
    
    fp = open(data_file, 'r')
    data = fp.read()
    fp.close()
    xor_data = []
    s = "0CTFc0MPR3s541gOr1tHmm3MEd4" + chr(0)
    for i in xrange(4, len(data)):
    	xor_data.append(chr(ord(s[(i-4)%len(s)]) ^ ord(data[i])))
    xor_data = ''.join(xor_data)
    
    ori_dict = {}
    ori_data = []
    
    for i in xrange(0, len(xor_data), 2):
    	if xor_data[i+1] == '\x00':
    		tmp = chr(0xff-ord(xor_data[i]))
    		ori_data.append(tmp)
    	else:
    		t = ord(xor_data[i]) + ord(xor_data[i+1])*256
    		if ori_dict.has_key(t):
    			ori_data.append(ori_dict[t])
    		else:
    			find = 0
    			for x in xrange(len(ori_data)):
    				for y in xrange(x, x+2):
    					tmp = ori_data[x] + ori_data[y][0]
    					ori_data.append(tmp)
    					if check(''.join(ori_data), data):
    						ori_dict[t] = tmp
    						find = 1
    						break
    					else:
    						ori_data.pop()
    				if find == 1:
    					break
    fp = open('oridata', 'w')
    fp.write(''.join(ori_data))
    fp.close()
