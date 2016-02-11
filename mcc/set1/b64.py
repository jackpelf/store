s = '49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d'
dict = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
s = s.decode('hex')
ans = ''
for i in range(len(s)/3):
	tmp = s[3*i: 3*i + 3]
	a = ord(tmp[0]) >> 2
	b = ((ord(tmp[0]) & 0x3) << 4) | ((ord(tmp[1]) & 0xf0) >> 4)
	c = ((ord(tmp[1]) & 0xf) << 2) | ((ord(tmp[1]) & 0xc0) >> 6)
	d = ord(tmp[2]) & 0x3f
	print a,b,c,d
	ans += dict[a]
	ans += dict[b]
	ans += dict[c]
	ans += dict[d]
if len(s)%3 == 0:
	pass
else:
	for i in range(3 - len(s) % 3):
		ans += '='

print ans	
	

