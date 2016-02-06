from z3 import *
HEXC = [ 0x37, 0x65, 0x35, 0x66, 0x34, 0x39, 0x63, 0x33, 0x62, 0x32, 0x36, 0x30, 0x61, 0x31, 0x38, 0x64, 0x65, 0x37, 0x39, 0x63, 0x33, 0x62]
FLG = [0xa4, 0xb3, 0x28, 0x2d, 0x9b, 0x93, 0xfe, 0x35, 0x75, 0xdc, 0x78, 0xb4, 0x3c, 0x81, 0x37]

x = [BitVec("x%d"% i, 32) for i in range(20)]
s = Solver()

for i in range(4):
	s.add(x[i] == 0)
s.add(x[19] == 0)
for i in range(15):
	s.add(x[i] ^ x[i+5] ^ FLG[i] == 0)
s.check()
ans = s.model()		
buf = [s.model()[x[i]].as_long() for i in range(20)]

m = [BitVec("m%d" % i, 32) for i in range(20)]
n = [BitVec("n%d" % i, 32) for i in range(20)]
s = Solver()

for i in range(20):
	s.add(m[i] >= 0, m[i] < 18)
	s.add(n[i] >= 0, n[i] < 20)
	s.add(((m[i] ^ n[i]) | (n[i] << 4)) ^ 0xC3 == buf[i])

print s.check()
ans2 = s.model()
m = [(ans2[m[i]]).as_long() for i in range(20)]
n = [(ans2[n[i]]).as_long() for i in range(20)]

flag = '32c3_' + ''.join( chr(HEXC[i + 2]) for i in m ) + ''.join( chr(HEXC[i]) for i in n )
print flag
