#include<stdio.h>
int main()
{
	long long i;
	long long p;
	for(i=200000; i<= 999999; i++)
	{
		int flag = 1;
		long long c=0;
		int buf[20];
		int t = i;
		int j;
		while(t)
		{
			buf[c] = t%10;
			c++;
			t /= 10;
			for(j=0; j<c-1; j++)
				if( buf[c-1] == buf[j])
					flag = 0;
		}
		/*
		*/
		c = 0;
		p = i*i;
		//printf("p: %ld", p);
		while(p)
		{
			buf[c] = p%10;
			c++;
			p /= 10;
		}
		//printf("c: %d\n:", c);
		//for(j=0; j<c; j++)
		//	printf("%d", buf[j]);
		t = i;
		while(t)
		{
			long long j;
			//printf("%d\n", t%10);
			for(j=0; j<c; j++)
				if(buf[j] == t%10)
					flag = 0;
			t /= 10;
		}
		if(flag)
			printf("%d\n", i);
//		getchar();
	}
	return 0;
}
