#include<stdio.h>
int main()
{
	long long i=-57469125044203;
	long long ans = -1536092243306511225;
	printf("%ld\n", 9468659231510783855*26729);
	while(1)
	{
		if(i%100000000000 == 0)
			printf("%ld\n", i);
		long long tmp = i*26729; 
		if(tmp == ans)
		{
			printf("found: %ld\n", i);
			break;
		}
		i--;
	}
	return 0;
}
