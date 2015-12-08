from pwn import *

e = '62271a4776335e3380304b6110e06500c6b2ed514e3673757081c0276fd57c677065cd6240305772474640660f8449141fe36907c7b050070115757748d343634694571165732c13ba30ad135ed70a61eab330152c2105444432c4763d84224133d721023cb70054b9c459303c9338743a536b4641c414770be40a7362a63074'
print e
def encode(a, lens):
	for i in xrange(lens):
		xor1 = i%8
		xor2 = i/8
		if xor1 != 0:
			xor1 = ord(a[i-1]) & 0xff
		if xor2 != 0:
			xor2 = ord(a[i-8]) & 0xff 
		a[i] =chr((ord(a[i]) & 0xff) ^ xor1 ^ xor2)
	return a
def decode(s, lens):
	for j in xrange(lens):
		i = len(s) - 1 -j
		xor1 = i%8
		xor2 = i/8
		if xor1 != 0:
			xor1 = ord(s[i-1]) & 0xff
		if xor2 != 0:
			xor2 = ord(s[i-8]) & 0xff 
		s[i] =chr((ord(s[i]) & 0xff) ^ xor1 ^ xor2)
	return s

def dfs(tree, index, res):		#cengci zhuan zhongxue
    global tt
    if index >=  bufsize*2:
        return None
    i = index * 2
    dfs(tree, i+1, res)
    res[tt] = tree[index]
    tt += 1
    dfs(tree, i+2, res)

def ddfs(tree, index, res):		#zhongxu zhuan cengci
    global tt
    if index >=  bufsize*2:
        return None
    i = index * 2
    ddfs(tree, i+1, res)
    res[index] = tree[tt]
    tt += 1
    ddfs(tree, i+2, res)
'''
		    0
	    1	           2
	3	4	5	6
 7
01234567	cengci
73140526	zhongxu
res = [0 for i in range(8)]

print 'should be:','73140526'
tt = 0
dfs(list('01234567'), 0, res)
print ''.join(res)

print 'should be:' + '01234567'
tt = 0
ddfs(list('73140526'), 0, res)
print ''.join(res)
'''



res = [0 for i in range(256)]
bufsize = 128
tt = 0
log.info('ddfs')
ddfs(list(e), 0, res)
print ''.join(res)


log.info('w2b')
res = ''.join(res).decode('hex')
print res



log.info('decode')
d = decode(list(res), len(res))
d = ''.join(d)
print d, len(d)

log.info('xor')
fin = ''

for j in range(18):
	fin += (chr(ord(d[j]) ^ 19))
	print (chr(ord(d[j]) ^ 19)),
print '\n' + fin
