import threading,time

def func():
	pass

def main():
    print 'starting '
    threadpool=[]
    for i in xrange(10):
        th = threading.Thread(target=func, args=())
        threadpool.append(th)

    for th in threadpool:
        th.start()

    for th in threadpool :
        threading.Thread.join( th )

    print 'Done'

if __name__ == '__main__':
        main()
