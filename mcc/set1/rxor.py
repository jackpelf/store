s = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal"
key = 'ICE'
ans = ''
for i in range(len(s)):
	ans += chr(ord(s[i]) ^ ord(key[i % 3]))
print ans.encode('hex')
