from z3 import *
x = BitVec('x', 64)
solve(x*26729 == -1536092243306511225)
