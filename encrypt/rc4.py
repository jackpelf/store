K = [31, 32, 45, 123, 54]
S = [i for i in range(256)]
T = [0 for i in range(256)]
k = []

for i in range(256):
	T[i] = K[i%len(K)]

j = 0
for i in range(256):
	j = (j+S[i]+T[i])%256
	tmp = S[j]
	S[j] = S[i]
	S[i] = tmp

context = [42, 234, 123, 43, 64, 23, 54,76 ,84]
ciphertext = []
for r in range(len(context)):
	i = (i+1)%256
	j = (j+S[i])%256
	tmp = S[j]
	S[j] = S[i]
	S[i] = tmp
	t = (S[i] + S[j])%256
	ciphertext[r] = S[t]^context[i]

print context
