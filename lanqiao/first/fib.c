#include<stdio.h>
#include<stdlib.h>
unsigned short store[1000001];
unsigned int fn_ = 1;
unsigned int fn = 0;
unsigned int tmp = 1;
int main()
{
	int i;
	for( i = 1; i<=1000000; i++ )
	{
		tmp = fn;
		fn = (fn + fn_)%10007;
		fn_ = tmp;
		store[i] = fn;
	}
	scanf("%d",&i);
	printf("%d\n",store[i]);
	return 0;
}
