from binascii import *

c = '363243354a3131303131393132304c'
c = a2b_hex(c)
res = ''
for i in c:
	res += chr(ord(i)+49)
print res
