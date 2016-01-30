#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int n;
	int i;
	for(i=1000; i<=9999; i++)
	{	
		if(i%10 == i/1000 && (i/10) % 10 == (i/100)%10 )
				printf("%d\n", i);
	}
	return 0;
}
