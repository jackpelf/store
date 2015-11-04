from z3 import *
import struct

prng_state = [BitVec("init_{0}".format(i), 32) for i in range(16)]


def iteration(i):
	b = prng_state[(i+13)&15] ^ prng_state[i] ^ (prng_state[i]<<16) ^ (prng_state[(i+13)&15]<<15)
	c = prng_state[(i+9)&15] ^ ( LShR(prng_state[(i+9)&15], 11) )
	
	prng_state[(i+10)&15] = c^b 
	
	next_i = (i+15)&15
	a = prng_state[next_i]
	v9 = (((32 * (c^b)) & 0xda442d24) ^ c ^ b) ^ b ^ a ^ (a<<2) ^ (b<<18) ^ (c<<28)
	prng_state[next_i] = v9
	return next_i




def aiteration(i):
    next_i = (i+15)&15

    b = prng_state[(i+13)&15] ^ prng_state[i] ^ (prng_state[i] << 16) ^ (prng_state[(i+13)&15] << 15)     
    c = prng_state[(i+9)&15] ^ ( prng_state[(i+9)&15] >> 11 )

    prng_state[(i+10)&15] = c ^ b

    a = prng_state[next_i]
    v9 =  (((32 * (c ^ b)) & 0xDA442D24) ^ c ^ b)^ b ^ a ^ (a << 2) ^ (b << 18) ^ (c << 28)

    prng_state[next_i] = v9

    return next_i


after_0_state_dump = """
0xf7ffc000: 0xef590f88  0x83ad59d1  0xd93c8e23  0x4430ec95
0xf7ffc010: 0x4bbed9c8  0x63c41b2f  0xa8917a45  0xf4cba336
0xf7ffc020: 0xc0ba8afc  0x442c47eb  0xabfadd00  0x24784029
0xf7ffc030: 0xa2012fe8  0x477a90eb  0x68fdf575  0xf79fcc39
"""

after_1_state_dump = """
0xf7ffc000: 0xef590f88  0x83ad59d1  0xd93c8e23  0x4430ec95
0xf7ffc010: 0x4bbed9c8  0x63c41b2f  0xa8917a45  0xf4cba336
0xf7ffc020: 0xc0ba8afc  0xcef17e7c  0xabfadd00  0x24784029
0xf7ffc030: 0xa2012fe8  0x477a90eb  0x8ee8b00c  0xf79fcc39
"""

def dump_to_values(dump):
    lines = dump.split("\n")[1:]
    just_data = "\n".join([line[12:] for line in lines])
    just_data = just_data.replace("0x","").replace("\n","  ").replace("  "," ").rstrip()
    values = [int(v,16) for v in just_data.split(" ")]
    return values

after_0_values = dump_to_values(after_0_state_dump)
after_1_values = dump_to_values(after_1_state_dump)

# Set up the inital known state
for i in range(16):
    prng_state[i] = BitVecVal( after_0_values[i], 32 )


# Do one iteration, this will have the index of 15, since it starts at zero
# and is reduced by one each time (and we've already been through one 
# iteration to get to this point)
iteration(15)

for i in range(16):
    print '_____'
    print prng_state[i]
# Now check the results equal the expected gathered state
for i in range(16):
    simplified = simplify( prng_state[i] )
    try:
        val = int(str(simplified))

        if val == after_1_values[i]:
            print "Match on state {0}: {1:x} == {2:x}".format(i, val, after_1_values[i])
        else:
            print "*** Mismatch on state {0}: {1:x} != {2:x}".format(i, val, after_1_values[i])
    except:
        print "Not fully simplified: ", simplified
