#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int buf[34];
int main()
{
	int n;
	int i,j;
	for(i = 0; i<34; i++)
		buf[i] = 0;
	buf[0] = 1;
	scanf("%d", &n);
	for(i=1; i<=n; i++)
	{
		for(j=0; j<i; j++)
		{
			printf("%d ", buf[j]);
		}
		for(j=i+1; j>0; --j)
		{
			buf[j] = buf[j] + buf[j-1];
		}
		puts("");
	}
	return 0;
}
