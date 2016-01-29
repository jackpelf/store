#include<stdio.h>
int store[200];
int main()
{	
	int n;
	scanf("%d", &n);
	int i,j;
	for(i=0; i<n; i++)
		scanf("%d",&store[i]);
	for(i=0; i<n; i++)
	{
		for(j=i+1; j<n; j++)
		{
			int tmp;
			if(store[i] > store[j])
			{
				tmp = store[i];
				store[i] = store[j];
				store[j] = tmp;
			}
		}
	}
	for(i=0; i<n; i++)
		printf("%d ", store[i]);
	putchar('\n');
	return 0;
}
