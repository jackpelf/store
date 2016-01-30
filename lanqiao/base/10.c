#include<stdio.h>
#include<stdlib.h>
#include<string.h>
long long buf[1000];
int main()
{
	int n;
	int i,min,max;
	long long sum;
	min = 1000000;
	max = -1000000;
	sum = 0;
	scanf("%d", &n);
	for(i = 0; i<n; i++)
		scanf("%ld", &buf[i]);
	for(i=0; i<n; i++)
	{
		if(buf[i] > max)
		{
			max = buf[i];
		}
		if(buf[i] < min)
		{
			min = buf[i];
		}
		sum += buf[i];
	}
	printf("%d\n%d\n%ld\n", max, min, sum);
	return 0;
}
