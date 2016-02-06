from pwn import *
from hashlib import *

base = [str(x) for x in range(10)] + [ chr(x) for x in range(ord('A'),ord('A')+6)]
def hex2dec(string_num):
    return str(int(string_num.upper(), 16))

def dec2bin(string_num):
    num = int(string_num)
    mid = []
    while True:
        if num == 0: break
        num,rem = divmod(num, 2)
        mid.append(base[rem])

    return ''.join([str(x) for x in mid[::-1]])

def hex2bin(string_num):
    return dec2bin(hex2dec(string_num.upper()))



r = remote('ctf.sharif.edu', 12432)
r.recvuntil('its of its MD5 is')
data = r.recv(22)
for a in range(256):
	for b in range(256):
		for c in range(256):
			for d in range(256):
				s = chr(a) + chr(b) + chr(c) + chr(d)
				md = md5(s)
				ans = md.hexdigest()
				if data == (hex2bin(ans)[:22]):
					print 'found'
					r.interactive()
