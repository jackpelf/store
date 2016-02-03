s = "OMQEMDUEQMEK"
print s
ans = ''
for i in s:
	ans += chr((ord(i) - 65 - (ord('M') - ord('A'))) % 26 + 65 )
print ans
