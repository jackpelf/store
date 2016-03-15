#include<stdio.h>
int main()
{
	unsigned long long n, m, p;
	scanf("%ld%ld%ld", &n, &m, &p);
	unsigned long long x = m,a = 1, b = 1, c;
	while(x)
	{
		c = b;
		b = a + b;
		a = c;
		printf("%d\n", b);
		x --;
	}
	return 0;
}
