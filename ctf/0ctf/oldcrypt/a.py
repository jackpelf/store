def split(ciphertext, keylength):
    l = [None] * keylength
    for i in xrange(len(ciphertext)):
        if (l[i%keylength] == None):
            l[i%keylength] = []
    l[i%keylength].append(ciphertext[i])
    return l

text = ''
with open('ciphertext') as f:
	text = f.read()

print split(text, 20)
