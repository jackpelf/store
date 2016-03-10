import sys
sys.setrecursionlimit(100000000)

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
def encrypt(m,e,n):
	return pow(m, e, n)
def decrypt(c,d,n):
	return pow(c, d, n)

def primet(n):
	ans = [2]
	for i in range(n)[3:]:
		isp = 1
		for j in ans:
			if i%j == 0:
				isp = 0
				break
		if isp==1:
			ans.append(i)
	return ans

if __name__ == '__main__':
	print primet(100)
