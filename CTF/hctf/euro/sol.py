#! /usr/bin/python
from binascii import *
from string import *
s = '\x7e\x27`7Hc626>'
res = ''
for i in s:
	res += chr( ord(i) ^ 7 )
print 'forward 10:',res

v1 = 'c'
v2 = '1'
v3 = 'c'
v4 = ' '
v5 = '1'
v6 = 's'
v7 = ' '
v8 = 'v'
v9 = '3'
v10 = 'r'


s = v1 + '\x6f\x20\x74\x68\x69\x73\x20\x69\x73\x20\x61\x20\x6E\x6F\x74\x20' + v2 + '\x69\x66\x66\x63\x75\x6C\x74\x20\x70\x72\x6F\x62\x6C\x65\x6D\x20' + v3 + '\x66\x20\x79\x6F\x75\x20\x68\x61\x76\x65\x20\x61\x20\x76\x65\x72' + v4 + '\x20\x67\x6F\x6F\x64\x20\x63\x6F\x6D\x70\x75\x74\x65\x2E\x42\x75' + v5 + '\x20\x69\x66\x20\x79\x6F\x75\x20\x64\x6F\x20\x6E\x6F\x74\x20\x68' + v6 + '\x76\x65\x20\x61\x20\x67\x6F\x6F\x64\x20\x63\x6F\x6D\x70\x75\x74' + v7 + '\x72\x2E\x49\x74\x20\x73\x65\x65\x6D\x73\x20\x74\x68\x61\x74\x20' + v8 + '\x68\x69\x73\x20\x70\x72\x6F\x62\x6C\x65\x6D\x20\x77\x69\x6C\x6C' + v9 + '\x74\x61\x6B\x65\x20\x61\x20\x6C\x6F\x74\x20\x6F\x66\x20\x74\x69' + v10 + '\x65\x2E\x42\x75\x74\x20\x6E\x6F\x74\x20\x74\x68\x69\x6E\x67\x20\x69\x73\x20\x69\x6D\x70\x6F\x73\x73\x69\x62\x6C\x65\x2E\x53\x6F\x20\x6A\x75\x73\x74\x20\x74\x72\x79\x20\x69\x74\x21\x21\x53\x6F\x6D\x65\x20\x74\x69\x6D\x65\x73\x2C\x54\x68\x65\x20\x74\x68\x69\x6E\x67\x20\x77\x65\x20\x73\x65\x65\x6D\x20\x69\x73\x20\x6E\x6F\x74\x20\x72\x65\x61\x6C\x6C\x20\x5B\x5D\x5B\x5D\x28\x29\x28\x29\x3C\x3E\x3C\x3E\x2E\x2E'

#find str1,str2
str1 = ''
str2 = ''
flag = 0
for i in s:
	if flag == 0:
		str1 += i	
		flag = 1
	else:
		str2 += i
		flag = 0
str1 = v1 + ' hsi  o ifutpolm' + v3 + ' o aeavr odcmueB' + v5 + 'i o onthv  odcmu' + v7 + '.tsesta hspolmwl' + v9 + 'aealto ieBtnttigi mosbeS uttyi!Sm ie,h hn ese sntral[[((<<.'
str2 = 'oti sant' + v2 + 'fcl rbe fyuhv  e' + v4 + 'go opt.u fyud o ' + v6 + 'eago optrI em ht' + v8 + 'i rbe iltk  o ft' + v10 + '.u o hn sipsil.ojs r t!oetmsTetigw emi o el ]]))>>.'


#brute force
for v1 in printable:
	#print 'looping ... '
	for v3 in printable:
		for v5 in printable:
			for v7 in printable:
				for v9 in printable:
					str1 = v1 + ' hsi  o ifutpolm' + v3 + ' o aeavr odcmueB' + v5 + 'i o onthv  odcmu' + v7 + '.tsesta hspolmwl' + v9 + 'aealto ieBtnttigi mosbeS uttyi!Sm ie,h hn ese sntral[[((<<.'
					if crc32(str1) == 570961634:
						print 'found'
						print v1 + v3 + v5 + v7 + v9


for v2 in printable:
	#print 'looping ... '
	for v4 in printable:
		for v6 in printable:
			for v8 in printable:
				for v10 in printable:
					str2 = 'oti sant' + v2 + 'fcl rbe fyuhv  e' + v4 + 'go opt.u fyud o ' + v6 + 'eago optrI em ht' + v8 + 'i rbe iltk  o ft' + v10 + '.u o hn sipsil.ojs r t!oetmsTetigw emi o el ]]))>>.'
					if crc32(str2) == -943542018:
						print 'found'
						print v2 + v4 + v6 + v8 + v10
