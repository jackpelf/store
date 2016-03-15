/*
0
*/

#include<stdio.h>
int main()
{
	int i,j,k;
	for(i=0; i<100; i++)
	for(j=0; j<100; j++)
	for(k=0; k<100; k++)
	{
		if((i*i + j*j + k*k) == 1000)
		{
			printf("%d %d %d\n", i, j, k);
			exit(0);
		}
	}
	return 0;
}

	
