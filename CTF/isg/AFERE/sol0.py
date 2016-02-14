f = open('AFERE.apk')
data = f.read()
f.close()
print len(data)	
res = list(data)

i = -4
while True:
	i = data.find("\x50\x4b\x03\x04", i+4)
	if i == -1:
		break
	res[i+6:i+7] = chr(ord(data[i+6:i+7]) & 0xfe)

i = -4
while True:
	i = data.find("\x50\x4b\x01\x02", i+4)
	if i == -1:
		break
	res[i+8:i+9] = chr(ord(data[i+8:i+9]) & 0xfe)

ans = ''.join(res)
print len(ans)	
fo = open('out.zip', 'wb')
fo.write(ans)
fo.close()
print 'done'
