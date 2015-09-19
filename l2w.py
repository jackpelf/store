from sys import *

f = open( argv[1] , "r+" )
context = f.read()
context = context.replace('\n', '\r\n')
f.seek(0, 0)
f.write(context)

f.close()


