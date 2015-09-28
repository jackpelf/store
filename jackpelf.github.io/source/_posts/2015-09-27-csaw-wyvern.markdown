---
layout: post
title: "csaw_wyvern"
date: 2015-09-27 23:46:51 +0800
comments: true
categories: 
---

###0x00 
前面的ascii码的和加上后一个ascii码等于储存在data数组中的数字

###0x01 sol

	raw = [100,214,266,369,417,527,622,733,847,942,1054,1106,1222,1336,1441,1540,1589,1686,1796,1891,1996,2112,2165,2260,2336,2412,2498,2575]

	tmp = 0
	res = ''
	for i in range(28):
		res += chr(raw[i] - tmp)
		tmp  = tmp+ord(res[i])


	print res
            
            
