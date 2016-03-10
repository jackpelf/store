from z3 import *
x = BitVec('x', 32)
y = BitVec('y', 32)
s = Solver()
#s.add(x>=0x27, x<=(0xffffffff-0x28))
s.add(y>=0x27, y<=(0xffffffff-0x28))
s.add((x+y)==0x81)
print s.check()
