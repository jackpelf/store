from z3 import *
x = BitVec('x', 64)
solve(x*26729 == 0xeaaeb43e477b8487L)
