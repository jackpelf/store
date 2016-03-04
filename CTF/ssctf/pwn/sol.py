s = '''
b2403b9?88924408|Next:id|Salt:5
59b6a64?58a85a2f|Next:w|Salt:a
ebcfd0b?dc532969|Next:eval|Salt:d
30cfce1?8f4fe85d|Next:bash|Salt:1
6e9b1036?8dd8d17|Next:ls|Salt:c
679df8e4?564b41e|Next:dir|Salt:f
316c49e5?833517c|Next:cd|Salt:8
93e200c3?f7cd9df|Next:mv|Salt:8
e875a2e?75a1a4a6|Next:cp|Salt:6
1eae257e?4aa9d5b|Next:pwd|Salt:6
3ad1439?585ac494|Next:tree|Salt:b
ad9f68f?9b296397|Next:apt|Salt:4
a8def39?67ea2d35|Next:mysql|Salt:e
568125ed?c3f6788|Next:php|Salt:7
92327e4c?43d619d|Next:head|Salt:4
bf3d9fe6?1d5a8e9|Next:tail|Salt:7
db62c11c?5ab251c|Next:cat|Salt:1
8eb99012?513f24f|->:grep|salt:f
9a1e7ba1?2c83d83|->:more|salt:7
aea4e328?1b6f750|->:less|salt:6
9200b67a?b7c3d0e|->:vim|salt:5
cdcd507?bb1864cd|->:nano|Salt:3
ad9f68f?9b296397|->:sed|Salt:4
2bca8ccb?946b7a0|->:awk|salt:d
83091ce2?c893686|->:ps|salt:3
aa0efb9e?9094440|->:top|salt:9
58544024?0f74fd6|->:kill|salt:3
210194c?75687be6|->:find|Salt:0
5c8cd5a?e6b01684|->:break|Salt:a
3afb633e?0cdf1b2|->:gcc|salt:6
72ffd8eb?81f4687|->:debug|salt:c
c30201f7?f142449|->:git|salt:0
f062936a?6d3c8bd|->:curl|salt:5
f062936a?6d3c8bd|->:wget|salt:5
8e4c41f2?47bfa2f|->:gzip|salt:8
6a60928b?5a7e228|->:tar|salt:8
5cb4d45b?d0e5624|->:ftp|salt:c
5568161?8cdf4ad2|->:ssh|Salt:8
74b5a98?c9bbd4b5|->:exit|Salt:c
'''
flag = ''
import hashlib
for each in s.split('\n'):
	for i in 'QWERTYUIOPASDFGHJKLZXCVBNM1234567890qwertyuiopasdfghjklzxcvbnm':
		m = hashlib.md5()
		m.update(i + each[-1:])
		if m.hexdigest()[8:24][:4] == each[:4]:
			flag += i
print len(flag)
print (flag)
