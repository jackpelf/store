#include<stdio.h>
int main()
{
	int i,j;
	for(i=2; i<40; i++)
		for(j=2; j<40; j++)
		{
			if( abs(i - j) <= 8)
			{
				if( (i+j)*6 == i*j)
				{
					printf("%d %d\n", i, j);
					exit(0);
				}
			}
		}
	return 0;
}
	
