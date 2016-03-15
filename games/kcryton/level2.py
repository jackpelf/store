l0 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
l1 = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm"

s = "YRIRY GJB CNFFJBEQ EBGGRA"
print s
ans = ''
for i in s:
	if i != ' ':
		ans += l0[l1.find(i)]
	else:
		ans += i
print ans
