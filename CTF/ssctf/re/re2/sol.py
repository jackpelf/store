




v0 = (181 - 1) ^ 2
print 'v0: ',v0

ans = 0
for one_xor in range(256):
	source2 = [0x57,0x78,0x7D,0x3E,0x4A,0x4C,0x5C,0x35,0x2A,0x23,0x50,0x7F,0x57,0x78,0x55,0x64,0x4B,0x42,0x25,0x35,0x22,0x66,0x48]
	for i in range( len(source2) ):
		source2[i] ^= one_xor
	ans = 0
	for i in source2:
		ans ^= i
	if v0 == ans:
		break;
print 'one_xor: ',one_xor

for i in range(256):
	if (0xff & ((i^0x5a & 0xff) + (i^0x42 & 0xff))) == one_xor:
		print 'found'
		print 'v0',i

exit(0)

exit(0)


def md():
	import hashlib

	ans = 'FBC4A31E4E17D829CA2242B2F893481B'
	l = [0xfd, 0xc5, 0xfd, 0xe7, 0xc5, 0xe7, 0xc7, 0xe5, 0xc7,0xdd,0xe5,0xdd]
	for num in range(256):
		tmp = [ num ^ item for item in l]
		text = ''.join( chr(i & 0xff) for i in tmp )
		m = hashlib.md5()
		m.update(text)
		res = m.hexdigest().upper()
		if ans == res:
			print 'found'
			print text
			print num
md()
source0 = [0x88,0xEC,0xFC,0x9E,0xB9,0xFC,0xB3,0xAE,0xFC,0x92,0xB3,0xA8,0xFC,0x88,0xB3,0xFC,0x9E,0xB9,0xF,0x88,0xB4,0xBD,0xA8,0xFC,0xB5,0xAF,0xFC,0x88,0xB4,0xB9,0xFC,0x8D,0xA9,0xB9,0xAF,0xA8,0xB5,0xB3,0xB2]
source1 = [0xF5,0xD0,0xDF,0xDC,0x99,0xD8,0xD5,0xCE,0xD8,0xC0,0xCA,0x99,0xD4,0xD8,0xD2,0xDC,0xCA,0x99,0xCC,0xCA,0x99,0xDB,0xD5,0xD8,0xDA,0xD2,0x99,0xD8,0xD7,0xDD,0x99,0xDB,0xD5,0xCC,0xDC,0x95,0xD8,0xD7,0xDD,0x99,0xCD,0xD1,0xD6,0xCA,0xDC,0x99,0xCE,0xD1,0xDC,0xCB,0xDC,0x99,0xCD,0xD1,0xDC,0x99,0xCE,0xD6,0xCC,0xD7,0xDD,0x99,0xD1,0xD8,0xDD,0x99,0xDB,0xDC,0xDC,0xD7,0x99,0xCD,0xD1,0xDC,0x99,0xCA,0xCD,0xCB,0xD6,0xD7,0xDE,0xDC,0xCA,0xCD,0x99,0xCE,0xD0,0xD5,0xD5,0x99,0xDB,0xDC,0xDA,0xD6,0xD4,0xDC,0x99,0xD8,0x99,0xC9,0xD5,0xD8,0xDA,0xDC,0x99,0xCE,0xD1,0xDC,0xCB,0xDC,0x99,0xCE,0xDC]
source3 = [0x57,0x78,0x7D,0x3E,0x4A,0x4C,0x5C,0x35,0x2A,0x23,0x50,0x7F,0x57,0x78,0x55,0x64,0x4B,0x42,0x25,0x35,0x22,0x66,0x48]
ans0 = 0
for i in source3:
	ans0 ^= i
ans1 = ans0 ^ 182
ans2 = []
for i in range(256):
	if ans1 == ( (i^0x5A) + (i^0x42) ):
		ans2.append(i)
ans5 = []
for j in ans2:
	ans4 = 0
	for i in source1:
		ans4 ^= i
	ans5.append(ans4 ^ j ^ 0xc6)
ans7 = []
for j in ans5:
	ans6 = 0
	for i in source0:
		ans6 ^= i
	ans7.append( j ^ ans6)
print ans7
	

print '----------'

from z3 import *

bf0 = BitVec('bf0', 8)
bf1 = BitVec('bf1', 8)
bf2 = BitVec('bf2', 8)
bf3 = BitVec('bf3', 8)

al = bf3 ^ 0x6f
bl = bf1 ^ 0x77
cl = bf2 ^ bf1 ^ bf3 
dl = bf0 ^ 0x66

bf1 = bf0 ^ 0x11
bf3 = bf0 ^ 0x9
bf2 = bf0 ^ 0x7e



print solve( (bf0 + bf1 + bf2 + bf3) == 0xdc and (bf1 ^ 0x77 ^ bf3 ^ 0x6f ^ bf1 ^ 0x77)  == (bf1 ^ 0x77) and (bf2 ^ bf1 ^ 0x77 ^ bf3 ^ 0x6f ^ 0x18) == (bf0 ^ 0x66) and (bf1 ^ 0x77) == (bf0 ^ 0x66))

'''
bl == cl
al == dl
bl == al
'''


bf2 = 102
bf3 = 38
bf0 = 38
bf1 = 0

stack0 = bf3 ^ 0x6f
stack1 = bf0 ^ 0x66
stack2 = bf2 ^ bf1 ^ 0x77 ^ bf3 ^ 0x6f ^ 0x18
stack3 = bf1 ^ 0x77 ^ bf3 ^ 0x6f ^ bf1 ^ 0x77


edx = (stack1 + stack2 + stack0 + stack3) >> 2
print 'edx:', edx
def f_x(l, magic):
	for i in range( len(l) ):
		l[i] ^= magic
	return l

for magic in range(256):
	source0 = [0x88,0xEC,0xFC,0x9E,0xB9,0xFC,0xB3,0xAE,0xFC,0x92,0xB3,0xA8,0xFC,0x88,0xB3,0xFC,0x9E,0xB9,0xF,0x88,0xB4,0xBD,0xA8,0xFC,0xB5,0xAF,0xFC,0x88,0xB4,0xB9,0xFC,0x8D,0xA9,0xB9,0xAF,0xA8,0xB5,0xB3,0xB2]
	t_source0 = f_x(source0, magic)
	ans = 0
	for i in t_source0:
		ans = (ans ^ i) & 0xff
	ans = (0xc6 ^ ans) & 0xff
	source1 = [0xF5,0xD0,0xDF,0xDC,0x99,0xD8,0xD5,0xCE,0xD8,0xC0,0xCA,0x99,0xD4,0xD8,0xD2,0xDC,0xCA,0x99,0xCC,0xCA,0x99,0xDB,0xD5,0xD8,0xDA,0xD2,0x99,0xD8,0xD7,0xDD,0x99,0xDB,0xD5,0xCC,0xDC,0x95,0xD8,0xD7,0xDD,0x99,0xCD,0xD1,0xD6,0xCA,0xDC,0x99,0xCE,0xD1,0xDC,0xCB,0xDC,0x99,0xCD,0xD1,0xDC,0x99,0xCE,0xD6,0xCC,0xD7,0xDD,0x99,0xD1,0xD8,0xDD,0x99,0xDB,0xDC,0xDC,0xD7,0x99,0xCD,0xD1,0xDC,0x99,0xCA,0xCD,0xCB,0xD6,0xD7,0xDE,0xDC,0xCA,0xCD,0x99,0xCE,0xD0,0xD5,0xD5,0x99,0xDB,0xDC,0xDA,0xD6,0xD4,0xDC,0x99,0xD8,0x99,0xC9,0xD5,0xD8,0xDA,0xDC,0x99,0xCE,0xD1,0xDC,0xCB,0xDC,0x99,0xCE,0xDC]
	t_source1 = f_x(source1, ans)
	ans = 0
	for i in t_source1:
		ans = (ans ^ i) & 0xff
	ans = (((ans ^ 0x5a) & 0xff) + ((ans ^ 0x42) & 0xff)) & 0xff
	source3 = [0x57,0x78,0x7D,0x3E,0x4A,0x4C,0x5C,0x35,0x2A,0x23,0x50,0x7F,0x57,0x78,0x55,0x64,0x4B,0x42,0x25,0x35,0x22,0x66,0x48]
	t_source3 = f_x(source3, ans)
	ans = 0
	for i in t_source3:
		ans = (ans ^ i) & 0xff
	ans = (ans ^ 2) & 0xff
	if ans + 1 == 181:
		print 'found',magic

	
	
	
	






v0 = (181 - 1) ^ 2
print 'v0: ',v0

ans = 0
for one_xor in range(256):
	source2 = [0x57,0x78,0x7D,0x3E,0x4A,0x4C,0x5C,0x35,0x2A,0x23,0x50,0x7F,0x57,0x78,0x55,0x64,0x4B,0x42,0x25,0x35,0x22,0x66,0x48]
	for i in range( len(source2) ):
		source2[i] ^= one_xor
	ans = 0
	for i in source2:
		ans ^= i
	if v0 == ans:
		break;
print 'one_xor: ',one_xor

for i in range(256):
	if (0xff & ((i^0x5a & 0xff) + (i^0x42 & 0xff))) == one_xor:
		print 'found'
		print 'v0',i

exit(0)






l = [92,  120,  50,  74,  102,  116,  103,  90,  103,  50]
ans = ''
for i in l:
	ans += chr( i^19 )
print ans


l = [122,93,67,70,71,19,117, 95, 82, 84, 9]
ans = ''
for i in l:
	ans += chr( i^19 )

