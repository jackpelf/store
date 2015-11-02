f = open('input', 'rb')
data = f.read()

iv = ['C', 'A', 'S', 'H']
key = ['B', 'I', 'Z', 'Z']

res = ''
for i in range(len(data)/4):
	for j in range(4):
		res += chr(ord(data[4*i+j]) ^ ord(iv[j]) ^ ord(key[j]))
		iv[j] = data[4*i+j]

fw = open('out.pdf', 'wb')
fw.write(res)
fw.close()
f.close()






