#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 10000
unsigned char g[N][N];
char isv[N];
int n,m;
int max = 0;
int maxn= 0;
int dfs(int x,int y,int sum)
{
	if(sum > max)
	{
		max = sum;
		maxn = y;
	}
	int i;
	for(i=1; i<=n; i++)
	{
		if(!isv[i] && g[y][i])
		{
			isv[i] = 1;
			dfs(y,i,sum+g[y][i]);
			isv[i] = 0;
		}
	}
	return 0;
}
int main()
{
	int i;
	memset(g, 0, sizeof(g));
	scanf("%d", &n);
	for(i=0; i<n-1; i++)
	{
		int x,y,v;
		scanf("%d%d%d", &x, &y, &v);
		g[x][y] = v;
		g[y][x] = v;
	}
	memset(isv, 0, sizeof(isv));
	isv[1] = 1;
	for(i=1; i<=n; i++)
	{
		if(!isv[i] && g[1][i])
		{
			isv[i] = 1;
			dfs(1,i,g[1][i]);
			isv[i] = 0;
		}
	}
	int ed0 = maxn;
	max = 0;
	memset(isv, 0, sizeof(isv));
	isv[maxn] = 1;
	for(i=1; i<=n; i++)
	{
		if(!isv[i] && g[maxn][i])
		{
			isv[i] = 1;
			dfs(maxn,i,g[maxn][i]);
			isv[i] = 0;
		}
	}
	printf("%d\n", 10*max + (1+max)*max/2);
	return 0;
}
