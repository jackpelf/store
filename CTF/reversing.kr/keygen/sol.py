s = '5B134977135E7D13'.decode('hex')
key = [16, 32, 48]
ans = ''
for i in range( len(s) ):
	ans += chr( ord(s[i]) ^ key[i % 3] )
print ans
