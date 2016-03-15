#include<stdio.h>
#include<stdlib.h>
int main()
{
	int *p;
	int n;
	puts("input n:");
	scanf("%d",&n);
	for(int i=1; i<n; i++)
	{
		p = malloc(i);
		printf("%3d---%p----%3d\n",i,p,*(p-1)&0xfffffff8);
	}
}
