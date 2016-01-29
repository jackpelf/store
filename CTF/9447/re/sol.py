from z3 import *

s = Solver()
ans = BitVecs(' '.join("a%d"%i for i in range(40)), 8)

for i in range(5):
	f = open("set%d.txt"%i)
	data = f.read().split('\n')
	doc = 0
	for i in data:
		if 'do' in i:
			doc = doc + 1
		if 'if' in i:
			tmp = []
			delta = 0
			delta = i.find('==', delta)
			tmp.append(int(i[delta + 3: delta + 6]))
			delta = i.find('==', delta + 2)
			tmp.append(int(i[delta + 3: delta + 6]))
			delta = i.find('==', delta + 2)
			tmp.append(int(i[delta + 3: delta + 6]))
#			print doc,tmp
			s.add( Or(ans[doc] == tmp[0], ans[doc] == tmp[1], ans[doc] == tmp[2]) )
	f.close()
print s.check()
print '99447{' + ''.join(chr(s.model()[i].as_long()) for i in ans[6:38]) + '}'
