#include<stdio.h>
#include<time.h>
int main()
{
	time_t t = time(0);// - 3600*5;
	printf("%d\n", t);
	return 0;
}
