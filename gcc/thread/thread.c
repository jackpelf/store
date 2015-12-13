#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

/*
gcc thread.c -pthread
*/

void *func(void *arg)
{
	printf("i am new thread!\n");
	sleep(4);
}


int main()
{
	pthread_t tid;
	if(pthread_create(&tid, NULL, func, NULL)!=0)
	{
		puts("create error");
		pthread_join(tid, NULL);
		exit(0);
	}
	puts("exiting");
	return 0;
}
