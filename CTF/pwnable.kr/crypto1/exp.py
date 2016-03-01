from pwn import *
import hashlib


def pwn(name):
	p = remote('pwnable.kr', 9006)
	p.recvuntil("ID")
	p.sendline(name)
	p.recvuntil("PW")
	p.sendline('')
	res = p.recvuntil("(")
	res = p.recvuntil(")")
	p.close()
	return res
id = 'admin'
cookie = 'you_will_never_guess_this_sugar_honey_salt_cookie'
print len(cookie)
pw = hashlib.sha256(id+cookie).hexdigest()
p = remote('pwnable.kr', 9006)
p.recvuntil("ID")
p.sendline(id)
p.recvuntil("PW")
p.sendline(pw)
p.interactive()



exit(0)
'''
'-'*13 -- c		''.rjust(61, '-')
'-'*15    try		''.rjust(63, '-')

'-'*12 -- co		rjust(60, '-')
'-'*14 -- ctry 		'y'.rjust(63, '-')
'''


cookie = ''
for index in range(62)[::-1]:
	real = pwn( '-' * index)[: 128]
	for i in '1234567890abcdefghijklmnopqrstuvwxyz-_':
		now  = pwn( cookie.rjust(63, '-') + i)[: 128]
		if now == real:
			cookie += i
			print cookie
			print len(cookie)
			break




exit(0)
i = -1
while True:
	i += 1
	p = remote('pwnable.kr', 9006)
	p.recvuntil("ID")
	name = 'a'*i
	p.sendline(name)
	p.recvuntil("PW")
	pw = ''
	p.sendline(pw)
	res = p.recvuntil("(")
	res = p.recvuntil(")")
	#print res[:-1]
	print i, len(res[:-1])/2
	raw_input()
