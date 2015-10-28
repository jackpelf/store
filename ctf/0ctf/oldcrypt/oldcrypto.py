#!/usr/bin/env python
# encoding: utf-8

tr = [
        [12, 9, 16, 3, 13, 15, 22, 17, 20, 1, 10, 24, 0, 4, 19, 5, 2, 7, 23, 14, 8, 21, 6, 18, 11, 25],
        [19, 16, 7, 5, 22, 3, 15, 2, 8, 14, 18, 17, 25, 13, 9, 6, 1, 11, 10, 0, 21, 20, 4, 23, 24, 12],
        [0, 7, 9, 14, 19, 8, 12, 1, 5, 2, 24, 11, 6, 21, 3, 15, 18, 25, 16, 4, 20, 13, 23, 22, 10, 17],
        [4, 15, 22, 13, 0, 10, 21, 14, 11, 19, 5, 8, 17, 3, 7, 1, 20, 12, 24, 9, 16, 6, 2, 25, 18, 23],
        [10, 23, 15, 25, 8, 16, 20, 21, 4, 11, 0, 9, 13, 12, 17, 2, 5, 14, 22, 24, 6, 7, 18, 1, 19, 3],
        [8, 10, 23, 7, 12, 6, 5, 3, 0, 18, 1, 14, 4, 22, 11, 21, 19, 20, 9, 16, 17, 15, 13, 2, 25, 24],
        [13, 19, 11, 15, 16, 22, 18, 23, 12, 24, 20, 2, 8, 0, 25, 3, 4, 21, 6, 1, 10, 17, 5, 7, 9, 14],
        [14, 2, 1, 24, 11, 23, 16, 20, 13, 10, 9, 4, 22, 8, 0, 25, 6, 19, 21, 17, 7, 18, 12, 5, 3, 15],
        [7, 4, 10, 21, 1, 20, 13, 0, 15, 12, 2, 18, 9, 6, 23, 8, 22, 24, 11, 25, 5, 3, 16, 14, 17, 19],
        [20, 1, 5, 16, 10, 2, 9, 19, 21, 6, 4, 25, 18, 24, 22, 23, 3, 17, 12, 7, 0, 8, 14, 15, 13, 11],
        [6, 13, 3, 2, 5, 4, 0, 9, 23, 7, 25, 21, 20, 1, 24, 18, 17, 16, 15, 19, 12, 11, 22, 8, 14, 10],
        [17, 6, 13, 23, 18, 19, 1, 16, 24, 25, 12, 15, 10, 2, 20, 11, 7, 0, 4, 5, 14, 22, 21, 3, 8, 9],
        [3, 22, 8, 0, 7, 21, 11, 4, 2, 16, 19, 6, 15, 25, 14, 12, 9, 23, 18, 10, 24, 5, 1, 17, 20, 13],
        [18, 3, 2, 1, 17, 12, 10, 24, 16, 9, 6, 19, 5, 23, 21, 22, 8, 4, 0, 11, 25, 14, 15, 13, 7, 20],
        [16, 24, 21, 12, 15, 14, 23, 18, 25, 20, 11, 10, 3, 17, 5, 4, 0, 13, 7, 22, 9, 2, 19, 6, 1, 8],
        [5, 17, 4, 19, 2, 0, 25, 22, 18, 23, 13, 16, 14, 10, 12, 20, 11, 1, 8, 3, 15, 24, 7, 9, 21, 6],
        [11, 8, 20, 22, 14, 7, 6, 5, 1, 21, 16, 0, 12, 19, 4, 17, 10, 15, 25, 13, 2, 9, 3, 24, 23, 18],
        [9, 21, 14, 17, 24, 5, 7, 6, 10, 0, 8, 23, 19, 15, 2, 13, 16, 3, 20, 12, 18, 1, 25, 11, 4, 22],
        [22, 5, 6, 20, 23, 1, 2, 25, 9, 8, 17, 13, 16, 11, 18, 24, 12, 10, 14, 21, 3, 19, 0, 4, 15, 7],
        [25, 18, 19, 8, 20, 17, 14, 12, 3, 13, 15, 22, 7, 9, 6, 10, 24, 5, 1, 2, 4, 23, 11, 21, 16, 0],
        [24, 20, 17, 9, 25, 13, 8, 11, 6, 3, 22, 7, 23, 5, 15, 14, 21, 2, 19, 18, 1, 16, 10, 12, 0, 4],
        [15, 25, 18, 10, 6, 9, 4, 13, 17, 5, 3, 20, 21, 7, 16, 0, 14, 8, 2, 23, 11, 12, 24, 19, 22, 1],
        [23, 14, 24, 18, 4, 25, 17, 7, 19, 22, 21, 12, 11, 20, 1, 16, 15, 6, 3, 8, 13, 10, 9, 0, 2, 5],
        [21, 11, 25, 6, 9, 18, 3, 10, 14, 4, 7, 1, 24, 16, 8, 19, 13, 22, 5, 15, 23, 0, 17, 20, 12, 2],
        [2, 12, 0, 4, 3, 11, 24, 15, 22, 17, 14, 5, 1, 18, 10, 7, 23, 9, 13, 20, 19, 25, 8, 16, 6, 21],
        [1, 0, 12, 11, 21, 24, 19, 8, 7, 15, 23, 3, 2, 14, 13, 9, 25, 18, 17, 6, 22, 4, 20, 10, 5, 16]
    ]

def encrypt(plaintext, key):
    ciphertext = ""
    for i in xrange(len(plaintext)):
        p = ord(plaintext[i]) - ord('a')
        k = ord(key[i % len(key)]) - ord('a')
        c = (tr[k][p] + i**7) % 26
        ciphertext += chr(c + ord('a'))
    return ciphertext

def decrypt(ciphertext, key):
    plaintext = ""
    for i in xrange(len(ciphertext)):
        c = ord(ciphertext[i]) - ord('a')
        k = ord(key[i % len(key)]) - ord('a')
        p = tr[k][(c - i**7) % 26]
        plaintext += chr(p + ord('a'))
    return plaintext

text = ''
with open('ciphertext') as f:
	text = f.read()

print decrypt(text, 'classicalcipherisfun')

