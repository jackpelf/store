#include<stdio.h>
#include<string.h>
char store[1000000];
int main()
{
	int r,c;
	int i;
	memset(store, 1, sizeof(store));
	for(r = 2; r <= 3; r++)
	{
		int p = 1;
		for(i=1; i<1000000; i++)
		{
			if(store[i] == 1)
			{
				if((p % r) == 0)
				{	
					store[i] = 0;
				}
				p++;
			}
		}
		for(i=1; i<40; i++)
			if(store[i] == 1)
				printf("%d\n", i);
		puts("_______");
	}
	int m,n;
	scanf("%d %d", &m, &n);
	return 0;
}
