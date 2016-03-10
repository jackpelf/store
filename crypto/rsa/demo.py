from num import *
p = 61
q = 53
n = p*q
print 'n:',n
fin = (p - 1) * (q - 1)
print 'fin :',fin
e = 17
d = modInv(e, fin)
public_key = (n, e)
private_key = (n, d)

print 'public_key: ',public_key
print 'private_key: ',private_key
m = 65
print 'plain text:', m
c = encrypt(m,e,n)
print 'encrypted text:', c
print 'decrypted text:', decrypt(c,d,n)

