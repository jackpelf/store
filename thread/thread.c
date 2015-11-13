#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *func(void *arg)
{
	printf("i am new thread!\n");
	printf("new thread PID :%d, TID :%d\n", getpid(), pthread_self());
}


int main()
{
	pthread_t tid;
	if(pthread_create(&tid, NULL, func, NULL)!=0)
	{
		puts("create error");
		exit(0);
	}
	printf("TID in thread :%d\n", tid);
	printf("Main PID :%d,TID :%d\n", getpid(), pthread_self());
	sleep(2);
	puts("exiting");
	return 0;
}
