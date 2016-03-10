from Crypto.Cipher import DES

key_hex = 'E1E1E1E1F0F0F0F0'
KEY = key_hex.decode("hex")
IV = '13245678'
f = open('ciphertext')
ciphertext = f.read()
a = DES.new(KEY, DES.MODE_OFB, IV)
plaintext = a.decrypt(ciphertext)
print plaintext
