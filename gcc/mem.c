#include<stdio.h>
#include<stdlib.h>

int main()
{
	int a1,a2;
	long long res;
	long *addr;
	long *addr1;
	long *addr2;
	__asm__ (	
			".intel_syntax noprefix\n"
			"MOV RAX,fs:[0]\n"
		:"=a"(res)		//output
		:			//input
		:			//register that will be changed
	); 
	getchar();
	//addr = malloc(139520);
	addr = malloc(135168);
	addr1 = malloc(13);
	addr2 = malloc(142349520);
	printf("tls:%p\n", res);
	printf("middle malloc:%p\n", addr);
	printf("small malloc:%p\n", addr1);
	printf("big malloc:%p\n", addr2);
	sleep(32232);

}
