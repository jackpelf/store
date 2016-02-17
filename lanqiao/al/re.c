#include<stdio.h>
int buf[10000];
int c = 0,n;

void re6()
{
	int i,tmp,sum;
	for(i = 100000; i <= 999999; i++)
	{
		tmp = i;
		sum = 0;
		while(tmp)
		{
			sum += tmp % 10;
			tmp = tmp / 10;
		}
		if(sum != n)
			continue;
		if(i % 10 == (i / 100000))
			if(((i/10) % 10) == (i / 10000) % 10)
				if(((i/100) % 10) == (i / 1000) % 10)
				buf[c++] = i;
	}
}
void re5()
{
	int i,tmp,sum;
	for(i = 10000; i <= 99999; i++)
	{
		tmp = i;
		sum = 0;
		while(tmp)
		{
			sum += tmp % 10;
			tmp = tmp / 10;
		}
		if(sum != n)
			continue;
		if(i % 10 == (i / 10000))
			if(((i/10) % 10) == (i / 1000) % 10)
				buf[c++] = i;
	}
}

int main()
{
	int i;
	scanf("%d", &n);
	re5();
	re6();
	if( c == 0)
	{
		puts("-1");
		return 0;
	}
	for(i = 0; i < c; i++)
	{
		printf("%d\n", buf[i]);
	}
	return 0;
}
