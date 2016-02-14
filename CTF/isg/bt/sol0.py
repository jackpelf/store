f = open('out.txt')
data = f.read()
f.close()
for i in data.split('\n'):
	if i == '':
		continue
	if 'Break' in i:
		continue
	if 'process' in i or 'command' in i or 'now' in i:
		continue
	if 'r3' in i:
		print i.split('	')[1],
		continue
	print i.split('	')[1]
