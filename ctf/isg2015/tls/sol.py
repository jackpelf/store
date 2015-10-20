from pwn import *
from zio import *

p = process('./tlc')
print p.recvuntil('key:')
data = p.recv(1024)
if 
print data
p.interactive()
