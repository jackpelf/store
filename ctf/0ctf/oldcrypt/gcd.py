def gcd(m,n):
    if m<n:
        small = m
    else:
        small = n
    for i in range (small,0,-1):
        if m % i == 0 and n %i == 0:
            return i
while True:
	m = int(raw_input()) 
	n = int(raw_input()) 
	res = gcd(m,n)
	print res
