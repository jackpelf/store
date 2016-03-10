#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/mman.h>
int main()
{
	printf("%d\n", PROT_READ);
	printf("%d\n", PROT_EXEC);
	printf("%d\n", PROT_WRITE);
	raise(19);
	sleep(2333330);
	return 0;
}
