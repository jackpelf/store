#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n;
int sum=0;
int isv[9];
char buf[10] = {0};
char *store = "123456789";
void dfs(int d)
{
	int i,j;
	if(d==9)
	{
		int a,b,c;
		int tmp=n;
		int len=0;
		while(tmp) {tmp /= 10;len++;}
		for(i=1; i<len; i++)
			for(j=i+1; j<9; j++)
			{
				char tc = buf[i];
				buf[i] = 0;
				a = atoi(buf);
				buf[i] = tc;
				tc = buf[j];
				buf[j] = 0;
				b = atoi(buf+i);
				buf[j] = tc;
				c = atoi(buf+j);
				if(b%c == 0)
				{
					if(a+b/c==n)
						sum++;
				}
			}
	}
	else
		for(i=0; i<9; i++)
		{	
			if(isv[i] == 0)
			{
				isv[i] = 1;
				buf[d] = store[i];
				dfs(d+1);
				isv[i] = 0;
			}
		}
}
int main()
{
	scanf("%d", &n);
	memset(isv, 0, sizeof(isv));
	dfs(0);
	printf("%d\n",sum);
	return 0;
}
