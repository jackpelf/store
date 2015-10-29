def normalize(ciphertext, key):
    plaintext = ""
    for i in xrange(len(ciphertext)):
        c = ord(ciphertext[i]) - ord('a')
        k = ord(key[i % len(key)]) - ord('a')
        p = tr[k][c]
        plaintext += chr(p + ord('a'))
    return plaintext

f = open('ciphertext', 'r')
ciphertext = f.read()

nciphertext = normalize(ciphertext)

for guessedkeylength in [4,5,10,20]:
    sp = split(nciphertext, guessedkeylength)

    key= ""
    for i in xrange(guessedkeylength):
        letter = chr(findkeyletter(sp[i]) + ord('a'))
        key += letter

    print "key: " + key
    print "plaintext: " + decryptnormalize(nciphertext, key)
