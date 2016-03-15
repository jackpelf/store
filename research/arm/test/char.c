#include<stdio.h>
int main()
{
	char buf[20];
	int i;
	for(i=0; i<20; i++)
		printf("%p\n", &buf[i]);
	return 0;
}
