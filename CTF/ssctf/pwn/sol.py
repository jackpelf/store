l0 =  [[7, 1, 1, 6, 7], [1, 1, 2, 4, 1, 1, 1], [1, 3, 1, 1, 1, 3, 1], [1, 3, 1, 1, 1, 2, 1, 1, 3, 1], [1, 3, 1, 1, 1, 1, 2, 1, 3, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1], [7, 1, 1, 1, 1, 1, 1, 1, 7], [4, 1, 1, 1], [2, 1, 2, 4, 4, 2], [1, 1, 1, 2, 1, 1, 1, 4, 2, 1], [1, 5, 2, 3, 2, 2, 1], [4, 2, 2, 1, 3], [1, 1, 3, 1, 1, 2, 1, 1, 2, 1], [1, 2, 1, 4, 1, 4], [1, 5, 2, 6, 2, 1], [2, 2, 1, 1, 6, 2, 3], [1, 2, 2, 2, 2, 2, 1, 1], [1, 2, 2, 3, 1, 1], [1, 3, 2, 1, 1, 1, 2], [3, 1, 1, 4, 2, 3], [3, 2, 8, 1], [2, 1, 1, 1, 1], [7, 2, 1, 4, 1, 1, 2], [1, 1, 1, 2, 1, 1, 2, 2], [1, 3, 1, 2, 1, 1, 1, 2, 5, 1], [1, 3, 1, 5, 1, 1, 1, 1], [1, 3, 1, 1, 4, 1, 1, 2], [1, 1, 2, 1, 3, 4, 1], [7, 3, 1, 3, 2, 1]]
l1 =  [[7, 3, 3, 2, 7], [1, 1, 2, 1, 1, 1], [1, 3, 1, 3, 1, 1, 1, 1, 3, 1], [1, 3, 1, 1, 2, 2, 1, 1, 1, 3, 1], [1, 3, 1, 1, 1, 4, 1, 1, 1, 3, 1], [1, 1, 2, 2, 1, 1, 1, 1], [7, 1, 1, 1, 1, 1, 1, 1, 7], [1, "1", 1, 1], [2, 3, 2, 1, 2, 1, 1, 2], [1, 2, 1, 1, 3, 5], [2, 4, 2, 1, 1, 1], [1, 1, 1, 2, 3, 2, 1], [1, 1, 2, 2, 1, 3, 1, 2], [2, 1, 1, 1, 3, 6, 1], [1, 2, 1, 1, 4, 1, 1], [2, 3, 5, 1, 1, 1, 1, 1], [1, 2, 1, 1, 1, 2, 1, 2], [1, 1, 1, 1, 1, 3, 2, 3, 3], [2, 1, 1, 6, 4, 1, 3], [1, 3, 1, 1, 2, 3, 1, 2], [1, 1, 4, 1, 1, 8], [2, 2, 2, 1, 1, 1], [7, 2, 3, 2, 1, 1, 1, 1], [1, 1, 1, 2, 1, 2, 1, 1], [1, 3, 1, 5, 1, 6, 2], [1, 3, 1, 2, 2, 1, 1, 1, 1], [1, 3, 1, 2, 1, 3, 1, 1, 1], [1, 1, 4, 1, 3, 1, 1], [7, 1, 1, 1, 1, 1, 2]]

print len(l0)
f = open('/share/gs14/out1.sgriddler', 'w')
f.write('MK Version 3.0\r\n\r\n29 29\r\n')
for i in range(31):
	f.write('\r\n')
for i in l0:
	f.write( ''.join(' '+str(item) for item in i[::-1]) + '\r\n')
f.write('\r\n')
for i in l1:
	f.write( ''.join(' '+str(item) for item in i[::-1]) + '\r\n')
f.close()
			