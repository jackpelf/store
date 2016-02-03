key = "686974207468652062756c6c277320657965".decode('hex')
s = "1c0111001f010100061a024b53535009181c".decode('hex')
ans = ''
for i in range(len(key)):
	ans += chr( ord(key[i]) ^ ord(s[i]) )
print ans.encode('hex')
