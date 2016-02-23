from pwn import *
from z3 import *
state = [BitVec("init_{0}".format(i), 32) for i in range(16)]
def iteration(i):
	next_i = (i+15)&15
	b = state[(i+13)&15] ^ state[i] ^ (state[i] << 16) ^ (state[(i+13)&15] << 15)
	c = state[(i+9)&15] ^ (LShR(state[(i+9)&15], 11)) 
	state[(i+10)&15] = c ^ b
	a = state[next_i]
	v9 = (((32*(c^b)) & 0xDA442D24) ^ c ^ b)^ b ^ a ^ (a << 2) ^ (b << 18) ^ (c << 28)
	state[next_i] = v9
	return next_i


r = remote('192.168.56.102', 6666)

def leak():
	r.recvuntil('Quit')
	r.sendline('3')
	line = r.recvline()
	line = r.recvline()
	line = line.split()
	return int(line[2], 16)
l = []
for i in range(16):
	l.append(leak())
print len(l)
print state
s = Solver()
idx = 15
for item in l:
	idx = iteration(idx)
	s.add(state[idx] == item + 1)
print (s.check())




#log.info(line)
r.interactive()
