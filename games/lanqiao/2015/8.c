#include<stdio.h>
int main()
{
	int n;
	scanf("%d", &n);
	int sum = n;
	do
	{
		int t = n / 3;
		n = n % 3 + t;
		sum += t;
	}while(n > 2);
	printf("%d\n", sum);
	return 0;
}
