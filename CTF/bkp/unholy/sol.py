from z3 import *
from struct import *
from xtea import *

y = [[383212,38297,8201833],[382494 ,348234985,3492834886],[3842947 ,984328,38423942839]]
n=[[5034563854941868,252734795015555591,55088063485350767967],[-2770438152229037,142904135684288795,-33469734302639376803],[-3633507310795117,195138776204250759,-34639402662163370450]]
x = []
x.append(BitVecs('0 1 2',32))
x.append(BitVecs('3 4 5',32))
x.append(BitVecs('6 7 8',32))
s = Solver()
for i in range(3):
	for j in range(3):
		s.add((x[i][0]*y[0][j] + x[i][1]*y[1][j] + x[i][2]*y[2][j]) == n[i][j])
l = []
if s.check() == sat:
	m = s.model()
	for i in range(3):
		for j in range(3):
			l.append(m[x[i][j]].as_long())
			print(m[x[i][j]].as_long())
l.append(1634947872)
c = ''
for i in l:
	c += pack('>I', i)
key = 'whatsgoingonhere'
x = new(key, mode=MODE_ECB)
p = x.decrypt(c)
print ''.join(i[::-1] for i in p[0::4])
