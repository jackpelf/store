#include<stdio.h>
#include<stdlib.h>

int main()
{
	char *a = "ia";
	char b[10] = "ib";
	for(int i=0; i<128; i++)
	{
		b[1] = i;
		printf("%-10x\n", memcmp(a,b,3));
	}
	return 0;
}
