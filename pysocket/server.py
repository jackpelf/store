import os
import sys
import socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('localhost', int(sys.argv[1])))
sock.listen(5)
con, addr = sock.accept()
while True:
	try:
		buf = con.recv(1)
		os.write(1, buf)
		con.send(buf)
	except:
		print 'error'
