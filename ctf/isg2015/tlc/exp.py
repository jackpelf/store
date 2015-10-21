import base64
from zio import *

def rot13(s):
	res = ''
	for i in s:
		d = ord(i)
		if d<65 or (d>ord('Z') and d<97) or d>ord('z'):
			res += chr(d)
		else:
			if d<97:
				d = chr((d-65+13)%26+65)
			else:
				d = chr((d-97+13)%26+97)
			res += d
	return res

def exp(s):
	io = zio('./tlc')
	io.read_until(':')
	io.writeline(s)
	try:
		io.read_until(':')
		data = io.readline()
		if 'ISG' in data:
			print data
		io.close()
	except:
		pass
print rot13('djslfkj==')
'''
f = open('key', 'r').readlines()
for line in f:
	try:
		#print (rot13(base64.encodestring(line.replace('\n', '').rjust(9, '0'))))
		exp(rot13(base64.encodestring(line.replace('\n', '').rjust(9, '0'))))
	except:
		pass


'''
f = open('key', 'r').readlines()
