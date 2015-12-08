import base64
import threading ,time
import threading,time
from zio import *

def rot13(s):
	res = ''
	for i in s:
		d = ord(i)
		if d<65 or (d>ord('Z') and d<97) or d>ord('z'):
			res += chr(d)
		else:
			if d<97:
				d = chr((d-65+13)%26+65)
			else:
				d = chr((d-97+13)%26+97)
			res += d
	return res

def exp(s):
	io = zio('./tlc')
	io.read_until(':')
	io.writeline(s)
	try:
		io.read_until(':')
		data = io.readline()
		io.close()
	except:
		pass


class myThread (threading.Thread) :
	def __init__(self, argv1) :
		super(myThread, self).__init__()
		self.argv1= argv1

	def run(self):
		exp(self.argv1)
def main():
	thpool=[]
	print 'starting '
	
	f = open('key', 'r')
	lines = f.readlines()
	for line in lines:
		t = rot13(base64.encodestring(line.replace('\n', '').rjust(9, '0')))
		print t
		print type(t)
		thpool.append(myThread(t))


	for th in thpool:
		th.start()

	for th in thpool:
		th.join()

	print 'Done'

if __name__ == '__main__':
        main()
