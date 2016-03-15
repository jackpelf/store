#include<stdio.h>
int store[100000];
int sum = 0;
int main()
{
	int n;
	int i,j;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &store[i]);
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(store[i] > store[j])	
				sum ++;
		}
	}
	printf("%d\n", sum);
	return 0;
}
