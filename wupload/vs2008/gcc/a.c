#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	write(1, "hhhkkkkkkkkk", 20);
	alarm(4);
	puts("hello world");
	return 0;
}
