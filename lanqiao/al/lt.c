#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 10
#define MAX 0x7fffffff
int g[N][N];
int visited[N];
int n;
int max=0;
int d0;
int d1;
void dfs(int i, int j, int cost);
int  main()
{
	int i,j;
	int a,b,c;
	scanf("%d", &n);
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
			g[i][j] = MAX;
		}
	}
	for(i=0; i<n - 1; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		g[a][b] = c;
		g[b][a] = c;
	}
	/*
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
			printf("%8x ", g[i][j]);
		}
		puts("");
	}
	*/
	int flag = 0;
	for(i = 1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
			if(g[i][j] != MAX && i != j)
			{
				flag = 1;
				memset(visited, 0, (n+1)*sizeof(int));
				visited[i] = 1;
				visited[j] = 1;
				dfs(i, j, g[i][j]);
				visited[i] = 0;
				visited[j] = 0;
			}
		}
		if(flag == 1)
			break;
		puts("not first");
	}
	//printf("d0: %d\n", d0);
	//printf("max: %d\n", max);
	i = d0;
	max = 0;
	for(j=1; j<=n; j++)
	{
		if(g[i][j] != MAX && i != j)
		{
			memset(visited, 0, (n+1)*sizeof(int));
			visited[i] = 1;
			visited[j] = 1;
			dfs(i, j, g[i][j]);
			visited[i] = 0;
			visited[j] = 0;
		}
	}
	//printf("d0: %d\n", d0);
	//printf("max: %d\n", max);
	printf("%d\n", (11 + 10 + max) * max /2);
				
	return 0;
}
void dfs(int i, int j, int cost)
{
	//printf("%d %d\n", i, j);
	int k;
	for(k=1; k<=n; k++)
	{
		//printf("MAXplace: %d :%d\n",j, k);
		//printf("value: %d \n",g[j][k]);
		if( g[j][k] == MAX || visited[k] == 1)
		{
			if(max < cost)
			{
//				printf("max: %d cost:%d\n",max, cost);
				max = cost;
				d0 = j;
			}
		}
		else if(visited[k] == 0)
		{
			visited[k] = 1;
			dfs(j, k, cost + g[j][k]);
			visited[k] = 0;
		}
	}
}
