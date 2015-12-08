def search(name, t):
	i = 0
	cipher = ''
	res = ''
	with open(name) as f:
		cipher = f.read().strip()
	while i < len(cipher):
		now = cipher[i:i+t]
		find = cipher[i+t:].find(now)
		if find != -1:
			print now, i+1
			res += now + ' ' + str(i) + '\n'
			print cipher[find+i+t:find+i+2*t],find+i+t+1
			print 'D-value: %5d\n'%(find+t)
			res += cipher[find+i+t:find+i+2*t] + ' ' + str(find+i+t) + '\n'
#			print now
#			print '%10d'%(i+1)
#			print '%10d'%(find+i+4)
		i += 1
	res = res.split('\n')
	res = sorted(res)
#	for i in res:
#		print i

search('ciphertext', 3)

