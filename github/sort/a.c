#include<stdio.h>

long long int data[10][2];

int main()
{

	int i,j;
	long long int t;	
	for(i=0;i<10;i++)
	{
		data[i][0]=0;
		data[i][1]=0;
	}
	for(i=0; i<5; i++)
	{
		for(j=0;j<10; j++)
		{
			scanf("%lld", &t);
			printf("%lld\n", data[0][0]);
			data[j][0] += t;
			data[j][1] += t;
			scanf("%lld", &t);
			data[j][0] += t;
			scanf("%lld", &t);
			data[j][1] += t;
		}
	}
	for(i=0;i<10;i++)
	{
		printf("%lld	",data[i][0]);
		printf("%lld\n",data[i][1]);
	}
}
