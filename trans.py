from sys import *

f = open(argv[1], 'r')
d = f.read()
d = d.replace("\n", '  \n')
f.close()
f = open(argv[1], 'w')
f.truncate()
f.write(d)
f.close()
