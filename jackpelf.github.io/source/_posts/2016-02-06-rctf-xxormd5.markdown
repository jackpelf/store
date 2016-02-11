---
layout: post
title: "rctf-xxormd5"
date: 2016-02-06 23:00:38 +0800
comments: true
categories: 
---
'''python
f = open('xmd5')
ans = ''
data = f.read()
s = '01780c4c109e3237120cfbbacb8f6a53'.decode('hex')

print len(s)
for i in range(len(data)):
	ans += chr( ord(s[i % len(s)]) ^ ord(data[i]) ^ 0x20)
print ans.encode('hex')
print ans
f.close()
'''
