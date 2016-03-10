#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int g[1000][1000];
char isv[1000];
int n,m;
int p,q;
int ans=0;
char sig[1000];
int dfs(int x,int y)
{
	if(y == q)
	{
		ans++;
		int t;
		for(t=1; t<=n; t++)
			if(!isv[t])
			{
				sig[t] = 0;
			}
	}
	int i;
	for(i=1; i<=n; i++)
	{
		if(!isv[i] && g[y][i])
		{
			isv[i] = 1;
			dfs(y,i);
			isv[i] = 0;
		}
	}
	return 0;
}
int main()
{
	int i;
	memset(g, 0, sizeof(g));
	scanf("%d%d", &n, &m);
	for(i=0; i<m; i++)
	{
		int x,y;
		scanf("%d%d", &x, &y);
		g[x][y] = 1;
		g[y][x] = 1;
	}
	scanf("%d%d",&p,&q);
	memset(isv, 0, sizeof(isv));
	memset(sig, 1, sizeof(sig));
	isv[p] = 1;
	for(i=1; i<=n; i++)
	{
		if(!isv[i] && g[p][i])
		{	
			isv[i] = 1;
			dfs(p,i);
			isv[i] = 0;
		}
	}
	ans = 0;
	for(i=1; i<=n; i++)
		ans += sig[i];
	printf("%d\n", ans-2);
	return 0;
}
