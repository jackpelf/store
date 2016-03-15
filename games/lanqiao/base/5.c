#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int n;
	scanf("%d",&n);
	int i;
	for(i=10000; i<=999999; i++)
	{	
		int tmp = i;
		int sum = 0;
		while(tmp / 10 != 0)
		{
			sum += tmp % 10;
			tmp = tmp / 10;
		}
		sum += tmp % 10;
		if(sum == n)
		{
			if(i>99999)
			{
				if(i%10 == i/100000 && (i/10) % 10 == (i/10000)%10 && (i/100)%10 == (i/1000)%10)
					printf("%d\n", i);
			}
			else
				if(i%10 == i/10000 && (i/10) % 10 == (i/1000)%10 )
					printf("%d\n", i);
		}
	}
	return 0;
}
