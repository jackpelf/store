from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes

key = b'Sixteen byte key'
iv = get_random_bytes(16)
cipher = AES.new(key, AES.MODE_CBC, iv)
msg = EncodeAES(cipher, 'Attack at dawn')
print msg
