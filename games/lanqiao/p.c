#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int g[10][10];
int isv[10][10] = {0};
int n,m;
int mx[] = {1,-1,0,0};
int my[] = {0,0,1,-1};
int sum = 0;
int ans[1000];
int c=0;
int dfs(int x,int y,int s,int d)
{
	printf("%d %d\n", s, sum);
	getchar();
	int i;
	if(s == sum/2)
	{
		ans[c++] = d;
		return 0;
	}
	for(i=0; i<4; i++)
	{
		int nx = x + mx[i];
		int ny = y + my[i];
		if(nx >= n || nx < 0 || ny < 0 || ny >= m)
			continue;
		if(isv[nx][ny])
			continue;
		if(nx == 0 && ny == 0)
			continue;
		isv[nx][ny] = 1;
		dfs(nx, ny, s + g[nx][ny], d+1);
		isv[nx][ny] = 0;
	}
	return 0;
}
int main()
{
	int i,j;
	scanf("%d%d", &n, &m);
	for(i=0; i<n; i++)
		for(j=0; j<m; j++)
		{
			scanf("%d", &g[i][j]);
			printf("%d\n", g[i][j]);
			sum += g[i][j];
		}
	isv[0][0] = 1;
	puts("sig");
	dfs(0, 0, g[0][0], 1);
	puts("sig");
	printf("%d\n", c);
	for(i=0; i<c; i++)
		printf("%d\n", ans[i]);
	return 0;
}
