# coding=utf-8
from os import *

res = popen("route print")
res = res.readlines()


data = ''
count = 0
for i in res:
	if count == 2:
		break
	if "==========" in i:
		count += 1
	if "¿í´øÁ¬½Ó" in i or "Atheros" in i:	
		data += ( i + '\n' )
data = data.split("\n")
s = 'net'
for i in data:
	s += i[0:3]
print s

system( s )
