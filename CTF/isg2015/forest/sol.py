s = 'VFT}E7gy4yfE7tuG6{'
ans = ''
for i in s:
	c = ord(i)
	if (c >= ord('a')) and (c <= ord('m')):
        	c = (c + 13)
        elif c >= ord('A') and c <= ord('M'):
                c = (c + 13)
        elif c >= ord('n') and c <= ord('z'):
        	c = (c - 13)
        elif c >= ord('N') and c <= ord('Z'):
        	c = (c - 13)
        elif i in '67452301>?':
        	c = (c ^ 6)
        else:
        	c = (c ^ 7)
        ans += chr(c) 
print ans
