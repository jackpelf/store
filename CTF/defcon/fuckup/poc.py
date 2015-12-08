from z3 import *
from pwn import *

prng_state = [BitVec("init_{0}".format(i), 32) for i in range(16)]

def un32(v):	return v&0xffffffff

def iteration(i):
	next_i = (i+15)&15

	b = prng_state[(i+13)&15] ^ prng_state[i] ^ (prng_state[i] <<16) ^ (prng_state[(i+13)&15]<<15)
	c = prng_state[(i+9)&15] ^ (LShR(prng_state[(i+9)&15], 11))
	
	prng_state[(i+10)&15] = c ^ b
	a = prng_state[next_i]
	v9 = (((32*(c^b)) & 0xda442d24) ^ c ^ b) ^ b ^ a ^ (a<<2) ^ (b<<18) ^ (c<<28)
	
	prng_state[next_i] = v9

	return next_i

def iteration_numbers(i):
	next_i = (i+15)&15
	
	b = prng_state[(i+13)&15] ^ prng_state[i] ^ un32(prng_state[i]<<16) ^ un32(prng_state[(i+13)&15]<<15)
	c = prng_state[(i+9)&15] = c ^ b 

	a = prng_state[next_i]
	v9 = (((32 * (c^b)) & 0xda442d24) ^ c ^ b ) ^ b ^ a ^ un32(a<<2) ^ un32(b<<18) ^ un32(c<<28)

	prng_state[next_i] = v9
	return next_i

def iteration_attempts(outputs):
	global prng_state
	s = Solver()

	it = 15

	for output in outputs:
		it = iteration(it)
		s.add(prng_state[it] == output + 1)
	return s

r = remote('192.168.56.101', 6666)
log.info("Gather the random outputs ....")

outputs = []
for i in range(16):
	r.recvuntil("Quit\n")
	r.sendline("3")
	response = r.recvline()
	current_random = int(response.split(' ')[2], 16)
	outputs.append(current_random)


s = iteration_attempts(outputs)
print s
print s.check()
print outputs









r.interactive()
