'''
store
[0]	[1]	[2]	[3]	[4]	[5]	[6]
	 0	 
'''
y = [3179,2649,729,48,487,3189,2177,2650,5789,4380,2160,1350,5789,1736,144,2160,4393,1014,5054,3755,49,5789,724,5067,6544,2160,3189,724,2160,4368,1743,720,1008,293]

tree = "g{3q9OLNZ_bVWCyJk  l  sh  c  ax  r  d6  A  MY  t  Iv  P  4u  i  TS  Q  eB  n  Xz  o  R7  H  U2  p  F5  G  Km  8  Dw  }  Ej  f  "

c = -1
f = {}

def bt(d, num):
	global c
	if c < len(tree):
		c += 1
		if  tree[c] == ' ':
			return 0
		f[num] = tree[c]
		d += 1
		map = {}
		map['v'] = {num: tree[c]}
		map['l'] = bt(d, num + 48*d)
		map['r'] = bt(d, num + 49*d)
		return map
	return 0


bt(0, 0)
ans = ''
for i in y:
	ans += f[i]
print ans
