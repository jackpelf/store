import sys
sys.setrecursionlimit(100000000)
p = 61
q = 53
n = p*q
print 'n:',n
fin = (p - 1) * (q - 1)
print 'fin :',fin
e = 17

def gcd(a, b):
	if b == 0:
		return a
	else:
		return gcd(b, a % b)

def extendedeuclid(a, b):
	if b == 0:
		return a, 1, 0
	else:
		g, x, y = extendedeuclid(b, a % b)
		return g, y, x - (a//b) * y

def modInv(e, fin):
	if gcd(e, fin) == 1:
		return extendedeuclid(e, fin)[1] % fin
	else:
		return 0

d = modInv(e, fin)
public_key = (n, e)
private_key = (n, d)

print 'public_key: ',public_key
print 'private_key: ',private_key


def encrypt(m):
	global e, n
	return pow(m, e, n)
def decrypt(c):
	global d, n
	return pow(c, d, n)

m = 65
print 'plain text:', m
c = encrypt(m)
print 'encrypted text:', c
print 'decrypted text:', decrypt(c)

