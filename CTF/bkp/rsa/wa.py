from sympy.solvers import solve
from sympy import Symbol

def partial_quotiens(x, y):
        pq = []
        while x != 1:
                pq.append(x / y)
                a = y
                b = x % y
                x = a
                y = b
        #print pq
        return pq

def rational(pq):
        i = len(pq) - 1
        num = pq[i]
        denom = 1
        while i > 0:
                i -= 1
                a = (pq[i] * num) + denom
                b = num
                num = a
                denom = b
        #print (num, denom)
	return (num, denom)

def convergents(pq):
        c = []
        for i in range(1, len(pq)):
                c.append(rational(pq[0:i]))
        #print c
        return c

def phiN(e, d, k):
        return ((e * d) - 1) / k

# e = 17993
# n = 90581
# wiener_attack(e, n) --> p =  239, q =  379

n = 0x9C2F6505899120906E5AFBD755C92FEC429FBA194466F06AAE484FA33CABA720205E94CE9BF5AA527224916D1852AE07915FBC6A3A52045857E0A1224C72A360C01C0CEF388F1693A746D5AFBF318C0ABF027661ACAB54E0290DFA21C3616A498210E2578121D7C23877429331D428D756B957EB41ECAB1EAAD87018C6EA3445
e = 0x466A169E8C14AC89F39B5B0357EFFC3E2139F9B19E28C1E299F18B54952A07A932BA5CA9F4B93B3EAA5A12C4856981EE1A31A5B47A0068FF081FA3C8C2C546FEAA3619FD6EC7DD71C9A2E75F1301EC935F7A5B744A73DF34D21C47592E149074A3CCEF749ECE475E3B6B0C8EECAC7C55290FF148E9A29DB8480CFE2A57801275

pq = partial_quotiens(e, n)
c = convergents(pq)
x = Symbol('x')
for (k, d) in c:
        if k != 0:
                y = n - phiN(e, d, k) + 1
                roots = solve(x**2 - y*x + n, x)
                if len(roots) == 2:
                        p = roots[0]
                        q = roots[1]
                        if p * q == n:
                                print 'p = ', p
                                print 'q = ', q
                                break
