
def cal(item):
	res = ''
	for i in range(4):
		print item%131
		res += chr(int(item%131))
		item = item/131
	return res[::-1]



g = [0xD50ADE5, 0E302789, 0xED66F1F, 0xCD463FF,0xE0D94DD,0xFA4461F,0xCD91DA2]

result = ''
for j in range(7):
	result += cal(g[j])
print result
