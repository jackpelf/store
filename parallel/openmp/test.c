/*
gcc test.c -fopenmp
*/

#include<omp.h>
#include<time.h>
#include<stdio.h>
int main()
{
	int i,j;
	time_t ts = time(0);
	#pragma omp parallel for
	for(i=0; i<0xffff; i++)
		for(j=0; j<0xffff; j++)
			i = i;
	time_t te = time(0);
	printf("time: %d\n",te - ts);
	
	return 0;
}
