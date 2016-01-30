#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int n;
	int i;
	for(i=100; i<=999; i++)
	{
		int a = i%10;
		int b = (i/10)%10;
		int c = (i/100)%10;
		if(i == (a*a*a + b*b*b + c*c*c))
			printf("%d\n",i);
	}
	return 0;
}
