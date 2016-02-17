'''
m^e % n == c
c^d % n == m

set c, d, n
'''

p = 61
q = 53
fn = 3120
e = 17

c = 2790
d = 2753
n = 3233

m = pow(c, d, n)
print 'plain text: ', m
