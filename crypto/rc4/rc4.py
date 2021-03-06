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

		
	def easy(self):		#generator
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
	t = tmp.easy()
	print t.next()
	print t.next()
