---  
layout: post  
title: "python_thread"  
date: 2015-10-21 13:33:14 +0800  
comments: true  
categories:   
---  
###0x00 threads  
  
	import threading ,time  
  
	class myThread (threading.Thread) :  
		def __init__(self, argv1) :  
			super(myThread, self).__init__()  
			self.argv1= argv1  
  
		def run(self):  
			pass  
  
	def main():  
		thpool=[]  
		print 'starting '  
  
		for i in xrange(10):  
			thpool.append(myThread(i,2))  
  
		for th in thpool:  
			th.start()  
  
		for th in thpool:  
			th.join()  
  
		print 'Done'  
  
	if __name__ == '__main__':  
		main()  
