from pwn import *
import os
import sys
if sys.argv[1] == '2':
	r = remote('socket2.lab.seclover.com', 52700)
elif sys.argv[1] == '1':
	r = remote('socket.lab.seclover.com', 52700)
else:
	exit(0)
r.recvuntil('Addr ')
r.sendline('alexandamiked@gmail.com')
r.recvuntil(':')
r.sendline('197328640')

def f(ifw = False):
	global r
	print 'sig'
	print r.recvuntil("\"col\":")
	cont = ''
	col  = 'l0 = ' + r.recvuntil(", \"row\":")[:-8] 
	col += '\n'
	cont += col
		
	row = r.recvuntil("}")[:-1] + '\n'
	cont += 'l1 = ' + row
	org = cont
	for i in range(2)[1:]:
		cont = org.replace('?',str(i))
	
		cont += '''
print len(l0)'''
		cont += '''
f = open('/share/gs14/out%d.sgriddler', 'w')
f.write('MK Version 3.0\\r\\n\\r\\n29 29\\r\\n')
for i in range(31):
	f.write('\\r\\n')
for i in l0:
	f.write( ''.join(' '+str(item) for item in i[::-1]) + '\\r\\n')
f.write('\\r\\n')
for i in l1:
	f.write( ''.join(' '+str(item) for item in i[::-1]) + '\\r\\n')
f.close()
			'''%i
		if( ifw == True):
			f = open('sol.py', 'w')
			f.write(cont)
			f.close()

			p = os.popen('python sol.py ') 
			res = p.read()
			print res
			#print res.replace('\'%d\''%i, str(i))
			#print res.replace('\'%d\''%i, str(i)).replace(',', '.').replace(']. [', '\n')
		
r.recvuntil("$")

r.sendline("sudo su")
f()
r.sendline("id")
f()
r.sendline("w")
f()
r.sendline("eval")
f()
r.sendline("bash")
f()
r.sendline("ls")
f()
r.sendline("dir")
f()
r.sendline("cd")
f()
r.sendline("mv")
f()
r.sendline("cp")
f()
r.sendline("pwd")
f()
r.sendline("tree")
f()
r.sendline("apt")
f()
r.sendline("mysql")
f()
r.sendline("php")
f()
r.sendline("head")
f()
r.sendline("tail")
f()
r.sendline("cat")
f()
r.sendline("grep")
f()
r.sendline("more")
f()
r.sendline("less")
f()
r.sendline("vim")
f()
r.sendline("nano")
f()
r.sendline("sed")
f()
r.sendline("awk")
f()
r.sendline("ps")
f()
r.sendline("top")
f()
r.sendline("kill")
f()
r.sendline("find")
f()
r.sendline("break")
f()
r.sendline("gcc")
f()
r.sendline("debug")
f()
r.sendline("git")
f()
r.sendline("curl")
f()
r.sendline("wget")
f()
r.sendline("gzip")
f()
r.sendline("tar")
f()
r.sendline("ftp")
f()
r.sendline("ssh")
f()
r.sendline("exit")
f(True)
r.interactive()


#siwebldcmcptamphtcgmlvnsaptkfbgdgcwgtfse
