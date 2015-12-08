
def sol(s):
	res = [' ' for i in range(3)]
	res[0] = chr((ord(s[0])*4 + (ord(s[1])>>4)&3)&0xff)
	res[1] = chr(((ord(s[1])-4)*16 + ord(s[0])*4)&0xff)
	res[2] = chr(((ord(s[1])&3)<<6 + ord(s[2]))&0xff)
	return ''.join(res)

cipher = 'w9zC67Oktsiyu7f7us8='

str = ''
for i in range(6):
	str += sol(cipher[3*i:3*i+3])

print str.encode('hex')
print str.decode('gbk')
print str.decode('utf8')
