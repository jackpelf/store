import socket
import os
import sys
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
	sock.connect(('localhost', int(sys.argv[1])))
	buf = raw_input("input text you want to send\n")
	sock.send(buf)
	print sock.recv(1024)
except:
	print 'error'
sock.close()

