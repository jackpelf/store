s = 'b5h760h64R867618bBwB48BrW92H4w5r'
s0 = 'b5h760h64R867618bBwB48BrW92H4w5r'
if s0 in s:
	print 'kjk'
for j in range(26):
	j = 21
	ans = ''
	for i in s:
		if i in '1234567890':
			ans += i
			continue
		if i in 'qwertyuiopasdfghjklzxcvbnm':
			ans += chr( ( j * (ord(i) - 97 - 28) ) % 26 + 97)
		else:
			ans += chr( ( j * (ord(i) - 65 - 28) ) % 26 + 65)
	print 'SSCTF{' + ans + '}'
