#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
int main()
{
	raise(19);
	
	sleep(2333330);
	return 0;
}
