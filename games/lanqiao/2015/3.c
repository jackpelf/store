/*
69
*/

#include<stdio.h>
#include<string.h>
int main()
{
	int buf[10] = {0};
	int c;
	int s,t;
	int i;
	for(i=0; i<1000; i++)
	{
		memset(buf, 0, sizeof(buf));
		c = 0;
		s = i*i;
		t = i*i*i;
		while(s)
		{
			buf[c++] = s % 10;
			s = s/10;
		}
		while(t)
		{
			buf[c++] = t % 10;
			t = t/10;
		}
		int j,k;
		for(j=0; j<10; j++)
			for(k=0; k<10; k++)	
			{
				if(buf[j] < buf[k])
				{
					int tmp = buf[j];
					buf[j] = buf[k];
					buf[k] = tmp;
				}
			}
		int flag = 1;	
		for(j=0; j<10; j++)
			if(buf[j] != j)
				flag = 0;
		if(flag)
		{
			printf("%d\n", i);
			printf("%d\n", i*i);
			printf("%d\n", i*i*i);
		}
	}
	return 0;
}
