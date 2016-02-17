l = [108,203,97,69,90,216,146,25,144,43,58,246,10,154,45,28]
ans = ''
for i in l:
	ans += hex(i)[-2:]
print len(ans)
print ans.upper()
