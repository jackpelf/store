'''
store
[0]	[1]	[2]	[3]	[4]	[5]	[6]
	 0	 
'''
y = [3179,2649,729,48,487,3189,2177,2650,5789,4380,2160,1350,5789,1736,144,2160,4393,1014,5054,3755,49,5789,724,5067,6544,2160,3189,724,2160,4368,1743,720,1008,293]

tree="g{3q9OLNZ_bVWCyJklshcaxrd6AMYtIvP4uiTSQeBnXzoR7HU2pF5GKm8Dw}Ejf"




f = open('f.txt')
data = f.read()
f.close()
f = {}
for i in data.split('\n'):
	tmp = i.split(' ')[::-1]
	if tmp == ['']:
		break
	f[tmp[0]] = tmp[1]
ans = ''
for i in y:
	ans += chr(int(f[str(i)]))
print ans
	
	
