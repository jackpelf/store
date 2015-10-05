---  
layout: post  
title: "bctf_freak"  
date: 2015-10-05 11:28:41 +0800  
comments: true  
categories:   
---  
###0x00  
  
first解密长度等于10进入second  
second   
decryptedData[i+1] ^ decryptedData[i] = Bctf2015[i]  
  
###0x01 sol  
爆破decryptedData  
  
rc4.py  
  
	class rc4():  
		def __init__(self, Key, plaintext):  
			self.i = 0  
			self.j = 0  
			self.r = 0  
			self.ciphertext = []  
			self.S = range(256)  
			self.plaintext = plaintext  
			self.Key= Key  
			self.rc4_init()  
		#init  
		def rc4_init(self):  
			T = [0 for i in range(256)] 	#tmp  
			for i in range(256):  
				T[i] = self.Key[i%len(self.Key)]  
			j = 0  
			for i in range(256):  
				j = (j+self.S[i]+T[i])%256  
				tmp = self.S[j]  
				self.S[j] = self.S[i]  
				self.S[i] = tmp  
		#encrypt  
		def rc4_crypt(self):  
			i = 0  
			j = 0  
			for r in range(len(self.plaintext)):  
				i = (i+1)%256  
				j = (j+self.S[i])%256  
		  
				tmp = self.S[j]  
				self.S[j] = self.S[i]  
				self.S[i] = tmp  
				  
				t = (self.S[i] + self.S[j])%256  
				self.ciphertext.append(self.S[t]^self.plaintext[r])  
			return self.ciphertext  
  
			  
		def gen(self):		#generator  
			i = 0  
			j = 0  
			for r in range(len(self.plaintext)):  
				i = (i+1)%256  
				j = (j+self.S[i])%256  
		  
				tmp = self.S[j]  
				self.S[j] = self.S[i]  
				self.S[i] = tmp  
				  
				t = (self.S[i] + self.S[j])%256  
				yield (self.S[t]^self.plaintext[r])  
  
	if __name__ == '__main__':  
		K = [31, 32, 45, 123, 54]			#key  
		context = [42, 234, 123, 43, 64, 23, 54,76 ,84]	#text  
		tmp = rc4(K, context)  
		t = tmp.gen()  
		print t.next()  
		print t.next()  
  
sol.py  
  
	from time import *  
	from rc4 import *  
	from string import *  
  
	d = [0 for i in range(10)]  
	s = 'BCTF2015!'  
	context = [0xc9, 0xd6, 0x90, 0x8f, 0x99, 0xe4, 0xa2, 0xe5, 0xf, 0xca, 0xd2, 0xae, 0x1e, 0x26, 0x92, 0x5, 0xc4, 0xe8, 0x3a, 0xc4, 0x20, 0x46, 0xd6, 0x6d, 0x8c, 0x9b, 0xed, 0x30, 0xe4, 0x8f, 0xd3, 0x3f, 0xa0, 0x71, 0xb8, 0xa5, 0x75, 0x3d, 0x7c, 0xff, 0x2e, 0x9, 0xc6, 0xf8, 0x83, 0x4, 0x2a, 0x77, 0x5a, 0x6, 0xeb ,0x66, 0x9f, 0xec, 0xb4, 0x2e, 0xfb, 0x47, 0xff, 0xf3, 0xcf, 0xab, 0x52, 0x5e, 0xd, 0x76, 0x5f, 0xa9, 0xe5, 0x68, 0xc1, 0xf7, 0x75, 0xe5, 0x51, 0x57, 0x5e, 0x00, 0xef, 0x18, 0x16, 0xdd, 0xaf, 0x9f, 0xbc, 0x2c, 0xe0, 0xf9, 0x8e, 0x19, 0xc1, 0xf4, 0xcc, 0xa3, 0x6a, 0x35, 0xf6, 0x95]  
  
	for i in range(256):  
		d[0] = i  
		for j in range(9):  
			d[j+1] = d[j]^ord(s[j])  
		text = rc4(d, context).rc4_crypt()  
		tmp = ''  
		for i in range(len(text)):  
			tmp += chr(text[i])  
		ok = 1  
		for i in tmp:  
			if i not in printable:  
				ok = 0  
				break  
		if ok==1:  
			print tmp  
  
  
  
  
###0x02 分解质因数  
CADO-NFS  
http://cado-nfs.gforge.inria.fr/#cont  
  
make   
make install  
./factor.sh zhishu -t 4 -s 4  
  
  
