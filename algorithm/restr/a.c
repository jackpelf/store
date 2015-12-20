#include<stdio.h>
#include<string.h>
int main()
{
	char buf[120000];	
	int i,j,max,n;
	while(scanf("%s", buf) != EOF)
	{
		max = 0;
		n = strlen(buf);
		for(i=1; i< n-1; i++)
		{
			if(max > 2*(i-1)+1 || max > 2*(n-i-1)+1)
				continue;
			for(j = 1;; j++)
			{
				if(i - j >= 0 && i + j < n)
				{
					if(buf[i-j] != buf[i+j])
					{
						if( 2*(j-1)+1 > max)
							max = 2*(j-1) + 1;
						break;
					}
				}
				else
				{
					if( 2*(j-1)+1 > max)
						max = 2*(j-1) + 1;
					break;
				}
			}
		}
		for(i=0; i< n-1; i++)
		{
			if(max > 2*(i+1) || max > 2*(n-i))
				continue;
			for(j = 0;; j++)
			{
				if(i - j >= 0 && i + 1 + j< n)
				{
					if(buf[i-j] != buf[i+1+j])
					{
						if( 2*j > max)
							max = 2*j;
						break;
					}
				}
				else
				{
					if( 2*j > max)
						max = 2*j;
					break;
				}
			}
		}
		printf("%d\n", max);
	}
}
