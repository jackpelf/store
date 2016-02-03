s = 'e4d03001e4c13001e2522001aafffffbe12fff1e'

ans = ''
for i in range(len(s)/2):
	ans += '\\x' + s[2*i: 2*i + 2]
print ans
