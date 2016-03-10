from Crypto.Cipher import DES

l = ['0000000000000000','FFFFFFFFFFFFFFFF','E1E1E1E1F0F0F0F0','1E1E1E1E0F0F0F0F','0101010101010101','FEFEFEFEFEFEFEFE','E0E0E0E0F1F1F1F1','1F1F1F1F0E0E0E0E']
key_hex = 'E1E1E1E1F0F0F0F0'
KEY = key_hex.decode("hex")
IV = '13245678'
f = open('ciphertext')
ciphertext = f.read()
a = DES.new(KEY, DES.MODE_OFB, IV)
plaintext = a.decrypt(ciphertext)
print plaintext
