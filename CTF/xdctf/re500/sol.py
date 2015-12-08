from binascii import *
from Crypto.Cipher import DES

m = [0xCF,0x77,0x48,0x09,0x7F,0xE3,0x21,0x6A,0xC5,0xFF,0x3E,0x44,0xF0,0x53,0xBB,0xF2]
for i in range(16):
	m[i] = m[i]^0xe4

#r left
c_m = [0 for i in range(16)]
for i in range(16):
	c_m[i] = m[(2+i)%16]


s = ''
for i in c_m:
	s += chr(i)
s += '\x08'*8

key = '\x34\x45\x86\x99\x1a\x4b\xcd\xa5'
cipher = DES.new(key, DES.MODE_ECB)
result = cipher.encrypt(s)

print b2a_hex(result).upper()



