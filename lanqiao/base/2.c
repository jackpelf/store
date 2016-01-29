#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	int n;
	int i,k;
	char buf[4];
	char store[100000];
	scanf("%d", &n);
	for(i=0; i<n; i++)
	{
		scanf("%s", store);
		int d = strlen(store) % 3;
		for(k=0; k<d; k++)
			buf[k] = store[k];
		buf[d] = 0;
		int tmp;
		sscanf(buf,"%x",&tmp);
		if(d != 0)
			printf("%o", tmp);
		int j;
		buf[3] = 0;
		for(j=0; j<(strlen(store)/3); j++)
		{
			buf[0] = store[3*j + d];
			buf[1] = store[3*j+1 + d];
			buf[2] = store[3*j+2 + d];
			int tmp;
			sscanf(buf,"%x",&tmp);
			printf("%o", tmp);
		}
		puts("");
	}	
	return 0;
}
