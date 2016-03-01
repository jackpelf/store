from pwn import *
import os
import sys
r = remote('socket2.lab.seclover.com', 52700)
print r.recvuntil('Addr ')
r.sendline('alexandamiked@gmail.com')
print r.recvuntil(':')
r.sendline('197328640')

def f():
	global r

	print r.recvuntil("$")
	r.sendline("sudo su")
	print r.recvuntil("\"col\":")
	cont = ''
	col  = 'l0 = ' + r.recvuntil(", \"row\":")[:-8] 
	col += '\n'
	cont += col
		
	row = r.recvuntil("}")[:-1] + '\n'
	cont += 'l1 = ' + row
	cont += '''
def mymax(l):
	max = 0
	for i in range( len(l) ):
		if max < len(l[i]):
			max = len( l[i] )
	return max
max0 = mymax(l0)
max1 = mymax(l1)
l = []
for j in range(max0):
	ans  = '\\t' * max1
	for i in range( len(l0) ):
		try:
			ans += str( l0[i][-1-j] )
			ans += '\\t'
		except:
			ans += '\\t'
	l.append(ans)
ans = l[::-1]
for i in ans:
	print i
for i in l1:
	ans = '\t' * (max1 - len(i))
	ans += ''.join(str(t) + '\t' for t in i)
	print ans

	
	
		'''
	f = open('sol.py', 'w')
	f.write(cont)
	f.close()

	print '-------'
	p = os.popen('python sol.py > out') 
	res = p.read()
	print res
	print '-------'
	
f()
r.interactive()
