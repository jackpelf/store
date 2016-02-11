from math import *
p = 991
q = 997
n = p*q		#public key
m = 234

def encrypt(m):
	return (m*m) % n

def decrypt(c):
	return int(sqrt(c) % p) 	#or mod q


c = encrypt(m)
print decrypt(c)
