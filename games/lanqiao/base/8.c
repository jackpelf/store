#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int buf[1000];
int main()
{
	int n;
	int i,s;
	scanf("%d", &n);
	for(i = 0; i<n; i++)
		scanf("%d", &buf[i]);
	scanf("%d", &s);
	for(i=0; i<n; i++)
	{
		if(s == buf[i])
		{
			printf("%d\n", i+1);
			break;
		}
	}
	if(i==n)
		puts("-1");

	return 0;
}
