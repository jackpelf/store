---
layout: post
title: "csaw_bricks"
date: 2015-11-02 12:46:47 +0800
comments: true
categories: 
--- 


###0x00
strings一下,可以发现iv  
通过iv和前4个字节可以计算出key

###0x01 sol

    f = open('input', 'rb')
    data = f.read()
    
    iv = ['C', 'A', 'S', 'H']
    key = ['B', 'I', 'Z', 'Z']
    
    res = ''
    for i in range(len(data)/4):
        for j in range(4):
    		res += chr(ord(data[4*i+j]) ^ ord(iv[j]) ^ ord(key[j]))
    		iv[j] = data[4*i+j]
    
    fw = open('out.pdf', 'wb')
    fw.write(res)
    fw.close()
    f.close
