/*
4356
*/
#include<stdio.h>
int main()
{
	int i,j;
	int buf[10];
	int c;
	int ans = 0;
	for(i=1; i<9999; i++)
		for(j=1; j<9999; j++)
		{
			int ti = i,tj = j;
			int p = i*j;
			c = 0;
			while(ti)
			{
				buf[c++] = ti % 10;
				ti /= 10;
			}
			while(tj)
			{
				buf[c++] = tj % 10;
				tj /= 10;
			}
			if(c != 4 )
				continue;
			if(buf[0] == buf[1] ||
			buf[0] == buf[2] ||
			buf[0] == buf[3] ||
			buf[1] == buf[2] ||
			buf[1] == buf[3] ||
			buf[2] == buf[3])
				continue;
			c = 0;
			while(p)
			{	
				c++;
				p /= 10;
			}
			if(c != 4)
				continue;
			p = i*j;
			int flag = 0;
			while(p)
			{
				int k;
				for(k=0; k<4; k++)
				{
					if( p%10 == buf[k] )
					{
						flag = 1;
					}
				}
				p /= 10;
			}
			if( !flag)
				continue;
			ans ++;
		}
	printf("ans: %d\n", ans/2);
	return 0;
}
	
