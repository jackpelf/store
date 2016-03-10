#include<stdio.h>
int main()
{
	int a,b,c;
	scanf("%d%d%d", &a, &b, &c);
	if(a>b && b>c)
		printf("%d %d %d\n", a, b, c);
	if(a>c && c>b)
		printf("%d %d %d\n", a, c, b);
	if(b>c && c>a)
		printf("%d %d %d\n", b, c, a);
	if(b>a && c<a)
		printf("%d %d %d\n", b, a, c);
	if(c>a && a>b)
		printf("%d %d %d\n", c, a, b);
	if(c>b && a<b)
		printf("%d %d %d\n", c, b, a);
	return 0;
}
	
