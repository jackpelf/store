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
