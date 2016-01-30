#include<stdio.h>
int main()
{
	int a,b,c;
	scanf("%d%d%d", &a, &b, &c);
	int i;
	for(i=1; i<0xffffffff; i++)
	{
		if(i%a == 0 && i%b == 0 && i%c == 0)
		{
			printf("%d\n", i);	
			break;
		}
	}
	return 0;
}
