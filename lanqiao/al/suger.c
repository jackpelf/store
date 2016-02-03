#include<stdio.h>
#include<string.h>
int work[1000];
int main()
{
	int n,i;
	int tmp[1000];
	int count = 0;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &work[i]);
	while(1)
	{
		for(i=0; i<n; i++)		//copy
		{
			tmp[i] = work[i];
		}
		for(i=0; i<n; i++)		
		{
			work[i] = tmp[i] / 2 + tmp[(i+1) % n] / 2;
		}
		for(i=0; i<n; i++)		
		{	
			if(work[i]%2 == 1)
			{
				work[i] ++;
				count ++;
			}
		}
		int flag = 1;
		for(i=1; i<n; i++)		
		{	
			if(work[i] != work[0])
			{
				flag = 0;
				break;
			}
		}
		if(flag)
			break;
	}
	printf("%d\n", count);
	return 0;
}
