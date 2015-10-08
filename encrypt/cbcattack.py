from Crypto.Cipher import AES
key = 'abcdefghijklmnop'
IV = 'abcdefghijklmnop'
KEYSIZE = 16
plaintext = 'dsjfklsssssssssssssssssssss'

def pad(instr, length):
        if(length == None):
                print "Supply a length to pad to"
        elif(len(instr) % length == 0):
                print "No Padding Needed"
                return instr
        else:
                return instr + '\x04' * (length - (len(instr) % length ))

def encrypt_block(key, plaintext):
        encobj = AES.new(key, AES.MODE_ECB)
        return encobj.encrypt(plaintext).encode('hex')

def decrypt_block(key, ctxt):
        decobj = AES.new(key, AES.MODE_ECB)
        return decobj.decrypt(ctxt).encode('hex')

plaintext = pad(plaintext, len(plaintext))
print plaintext
t = AES.new(key, AES.MODE_CBC, IV)
res = t.encrypt(plaintext).encode('hex')
print res
