'''
bi	0	2	3	4
bi2	1	3	4	4

d0	d[0]		d[3]


  5 d0      d[0]            d[3]
d1	d[1]		0
d2	d[2]		0

'''
from base64 import *
from Crypto.Cipher import DES
a = 'S4wp902KOV7QRogXdIUCMW1/ktz8sa5c3xePGfENuDTvBFqAmrbnLlHZYyhJij6+'
s = 'OKBvTrSKXPK3cObqoS21IW7Dg0eZ2RTYm3UrdPaVTdY'

l = []
for i in s:
	l.append(a.index(i))
res = []
for i in range(len(l) / 4):
	item = l[4*i: 4*i + 4]
	d0 = (((item[0] & 0x3f) << 2) | ((item[1] & 0x30) >> 4))
	d1 = ((item[1] & 0x0f) << 4) | ((item[2] & 0x3c) >> 2)
	d2 = ((item[2] & 0x03) << 6) | ((item[3] & 0x3f))
	res.append(d0)
	res.append(d1)
	res.append(d2)
ans = ''.join(chr(i) for i in res)
ans = ans[:-6]
key = "Mem3d4Da"
cipher = DES.new(key, DES.MODE_ECB)
print cipher.decrypt(ans)

