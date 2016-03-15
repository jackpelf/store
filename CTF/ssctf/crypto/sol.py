import sys
import string
def LShift(t, k):
    k %= 8
    return ((t << k) | (t >> (8 - k))) & 0xff


def encode(p):
    ret = ""
    for i in range(8):
        ret = ('|' if (p >> i) & 1 else 'O') + ret
    return ret


A = [85, 128, 177, 163, 7, 242, 231, 69, 185, 1, 91, 89, 80, 156, 81, 9, 102, 221, 195, 33, 31, 131, 179, 246, 15, 139, 205, 49, 107, 193, 5, 63, 117, 74, 140, 29, 135, 43, 197, 212, 0, 189, 218, 190, 112, 83, 238, 47, 194, 68, 233, 67, 122, 138, 53, 14, 35, 76, 79, 162, 145, 51, 90, 234, 50, 6, 225, 250, 215, 133, 180, 97, 141, 96, 20, 226, 3, 191, 187, 57, 168, 171, 105, 113, 196, 71, 239, 200, 254, 175, 164, 203, 61, 16, 241, 40, 176, 59, 70, 169, 146, 247, 232, 152, 165, 62, 253, 166, 167, 182, 160, 125, 78, 28, 130, 159, 255, 124, 153, 56, 58, 143, 150, 111, 207, 206, 32, 144,
     75, 39, 10, 201, 204, 77, 104, 65, 219, 98, 210, 173, 249, 13, 12, 103, 101, 21, 115, 48, 157, 147, 11, 99, 227, 45, 202, 158, 213, 100, 244, 54, 17, 161, 123, 92, 181, 243, 184, 188, 84, 95, 27, 72, 106, 192, 52, 44, 55, 129, 208, 109, 26, 24, 223, 64, 114, 19, 198, 23, 82, 120, 142, 178, 214, 186, 116, 94, 222, 86, 251, 36, 4, 248, 132, 25, 211, 199, 30, 87, 60, 127, 155, 41, 224, 151, 237, 136, 245, 37, 170, 252, 8, 42, 209, 46, 108, 88, 183, 149, 110, 66, 235, 229, 134, 73, 38, 118, 236, 119, 154, 216, 217, 240, 22, 121, 174, 93, 126, 230, 228, 18, 148, 220, 172, 2, 137, 34]
B = [0, 2, 3, 7, 1, 5, 6, 4]
C = [179, 132, 74, 60, 94, 252, 166, 242, 208, 217, 117, 255, 20, 99, 225, 58, 54, 184, 243, 37, 96, 106, 64, 151, 148, 248, 44, 175, 152, 40, 171, 251, 210, 118, 56, 6, 138, 77, 45, 169, 209, 232, 68, 182, 91, 203, 9, 16, 172, 95, 154, 90, 164, 161, 231, 11, 21, 3, 97, 70, 34, 86, 124, 114, 119, 223, 123, 167, 47, 219, 197, 221, 193, 192, 126, 78, 39, 233, 4, 120, 33, 131, 145, 183, 143, 31, 76, 121, 92, 153, 85, 100, 52, 109, 159, 112, 71, 62, 8, 244, 116, 245, 240, 215, 111, 134, 199, 214, 196, 213, 180, 189, 224, 101, 202, 201, 168, 32, 250, 59, 43, 27, 198, 239, 137, 238, 50,
     149, 107, 247, 7, 220, 246, 204, 127, 83, 146, 147, 48, 17, 67, 23, 93, 115, 41, 191, 2, 227, 87, 173, 108, 82, 205, 49, 1, 66, 105, 176, 22, 236, 29, 170, 110, 18, 28, 185, 235, 61, 88, 13, 165, 188, 177, 230, 130, 253, 150, 211, 42, 129, 125, 141, 19, 190, 133, 53, 84, 140, 135, 10, 241, 222, 73, 12, 155, 57, 237, 181, 36, 72, 174, 207, 98, 5, 229, 254, 156, 178, 128, 55, 14, 69, 30, 194, 122, 46, 136, 160, 206, 26, 102, 218, 103, 139, 195, 0, 144, 186, 249, 79, 81, 75, 212, 234, 158, 163, 80, 226, 65, 200, 38, 187, 113, 63, 24, 25, 142, 51, 228, 35, 157, 216, 104, 162, 15, 89]
D = [2, 4, 0, 5, 6, 7, 1, 3]
ans = 'OO|OO||OO|||||OO|OO||O||O|O||O|||O|OOOOOOO|O|O|O|||||OO|||O|||OO||O|OOOOOO|O|OO|OO||||OO|||OOOO|||||O||||O|OO|O|O|O||OO|O||O|OO|O||O|||O||O|OO|OOOOOO||OOO|O|O|O|||O|OO|O|O||O||O||OOOOO|||OO|O|'
print ans
print len(ans)
realkey = ''

for time in range(8):
	for each in string.printable:
		plain = bytearray("asdfghjk123456")
		key = bytearray( (realkey + each).ljust(8, 'a') )
		assert len(key) == 8
		t1 = bytearray()
		for i in plain:
		    t1.append(A[i])
		t2 = bytearray()
		for i in range(len(t1)):
		    t2.append(LShift(t1[i], B[i % 8]))
		for times in range(16):
		    for i in range(len(t2)):
			t2[i] = C[t2[i]]
		    for i in range(len(t2)):
			t2[i] = LShift(t2[i], i ^ D[i % 8])
		    for i in range(len(t2)):
			t2[i] ^= key[i % 8]
		out = ""
		for i in t2:
		    out += encode(i)
		if out[time*8: 8 + time*8] == ans[time*8:8 + time*8]:
			if (64+8+time*8) < len(out):
				if out[64 + time*8: 64 + 8 + time*8] == ans[64 + time*8:64 + 8 + time*8]:
					realkey += each
					break
			else:
					realkey += each
					break
	print realkey,len(realkey)

print realkey
	# out>>
	# OO|OO||OO|||||OO|OO||O||O|O||O|||O|OOOOOOO|O|O|O|||||OO|||O|||OO||O|OOOOOO|O|OO|OO||||OO|||OOOO|||||O||||O|OO|O|O|O||OO|O||O|OO|O||O|||O||O|OO|OOOOOO||OOO|O|O|O|||O|OO|O|O||O||O||OOOOO|||OO|O|

flag = 'OO||O||O|O|||OOOO||||||O|O|||OOO||O|OOOO||O|O|OO|||||OOOO||||O||OO|OO||O||O|O|O|||||OOOOOO|O|O||OOOOOOO||O|||OOOO||OO|OO|||O|OO|O|||O|O|OO|OOOO|OOO|OOO|OOOO||O|OO||||OO||||OOO|O|O||OO||||O||OOO|||O|OO|OO||OO||OOOO|O|'
ans = ''
for time in range( len(flag) / 8):
	for each in string.printable:
		plain = bytearray( (ans + each).ljust(len(flag)/8, 'a' ) )
		key = bytearray( '^&#qD93_' )
		assert len(key) == 8
		t1 = bytearray()
		for i in plain:
		    t1.append(A[i])
		t2 = bytearray()
		for i in range(len(t1)):
		    t2.append(LShift(t1[i], B[i % 8]))
		for times in range(16):
		    for i in range(len(t2)):
			t2[i] = C[t2[i]]
		    for i in range(len(t2)):
			t2[i] = LShift(t2[i], i ^ D[i % 8])
		    for i in range(len(t2)):
			t2[i] ^= key[i % 8]
		out = ""
		for i in t2:
		    out += encode(i)
		if flag[8*time: 8*(time + 1)] == out[8*time: 8*(time + 1)]:
			ans += each 	
			break
print ans