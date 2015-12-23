#include<stdio.h>
#include<string.h>
int main()
{
	char tmp[120000];	
	char buf[240000];	
	char p[240000];	
	int i,m,id,mx,max;
	while(scanf("%s", tmp) != EOF)
	{
		m = strlen(tmp);
		for(i=0; i<m; i++)
		{
			buf[2*i] = '#';
			buf[2*i+1] = tmp[i];
		}
		buf[2*i] = '#';
		buf[2*i+1] = 0;
		id = 0;mx = 0;max = 0;
		memset(p,0,2*m);
		for(i=0; buf[i]; i++)
		{
			if(mx >= i)
			{
				p[i] = mx-i< p[2*id-i] ? mx-i : p[2*id-i] ;
			}
			else
			{
				p[i] = 1;
			}

			while(i+p[i] <= 2*m && buf[i + p[i]] == buf[i - p[i]] && i-p[i] >= 0)
			{
				p[i]++;
			}
			
			if(i + p[i] > mx)
			{
				mx = i+p[i];
				id = i;
			}
			max = p[i] > max ? p[i] : max;
		}
		printf("%d\n",max - 1);
	}
}
