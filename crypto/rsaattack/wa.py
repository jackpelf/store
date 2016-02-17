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

e = 0x0285f8d4fe29ce11605edf221868937c1b70ae376e34d67f9bb78c29a2d79ca46a60ea02a70fdb40e805b5d854255968b2b1f043963dcd61714ce4fc5c70ecc4d756ad1685d661db39d15a801d1c382ed97a048f0f85d909c811691d3ffe262eb70ccd1fa7dba1aa79139f21c14b3dfe95340491cff3a5a6ae9604329578db9f5bcc192e16aa62f687a8038e60c01518f8ccaa0befe569dadae8e49310a7a3c3bddcf637fc82e5340bef4105b533b6a531895650b2efa337d94c7a76447767b5129a04bcf3cd95bb60f6bfd1a12658530124ad8c6fd71652b8e0eb482fcc475043b410dfc4fe5fbc6bda08ca61244284a4ab5b311bc669df0c753526a79c1a57
n = 0x02aeb637f6152afd4fb3a2dd165aec9d5b45e70d2b82e78a353f7a1751859d196f56cb6d11700195f1069a73d9e5710950b814229ab4c5549383c2c87e0cd97f904748a1302400dc76b42591da17dabaf946aaaf1640f1327af16be45b8830603947a9c3309ca4d6cc9f1a2bcfdacf285fbc2f730e515ae1d93591ccd98f5c4674ec4a5859264700f700a4f4dcf7c3c35bbc579f6ebf80da33c6c11f68655092bbe670d5225b8e571d596fe426db59a6a05aaf77b3917448b2cfbcb3bd647b46772b13133fc68ffabcb3752372b949a3704b8596df4a44f085393ee2bf80f8f393719ed94ab348852f6a5e0c493efa32da5bf601063a033beaf73ba47d8205db

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
