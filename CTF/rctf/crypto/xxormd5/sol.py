f = open('xmd5')
ans = ''
data = f.read()
s = '01780c4c109e3237120cfbbacb8f6a53'.decode('hex')

print len(s)
for i in range(len(data)):
	ans += chr( ord(s[i % len(s)]) ^ ord(data[i]) ^ 0x20)
print ans.encode('hex')
print ans
f.close()

