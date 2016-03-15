#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int g[10][10];
int isv[10][10] = {0};
int n,m;
int movx[] = {0,0,-1,1};
int movy[] = {-1,1,0,0};
int c=0;
int sum=0;
int ans[100];
int dfs(int x,int y,int cost,int d)
{
	int nx,ny;
	int i;
	if(sum/2 == cost)
	{
		ans[c++] = d;
		return;
	}
	if(sum/2 < cost)
		return;
	for(i=0; i<4; i++)
	{
		nx = x+movx[i];
		ny = y+movy[i];
		if(nx>=n || nx<0 || ny>=m || ny <0)
			continue;
		if(isv[nx][ny])
			continue;
		isv[nx][ny] = 1;
		dfs(nx,ny,cost+g[nx][ny],d+1);
		isv[nx][ny] = 0;
	}
}
int main()
{
	int i,j;
	scanf("%d%d", &m, &n);
	for(i=0; i<n; i++)
		for(j=0; j<m; j++)
		{
			scanf("%d",&g[i][j]);
			sum += g[i][j];
		}
	isv[0][0] = 1;
	dfs(0,0,g[0][0],1);
	int min = 1000;
	for(i=0; i<c; i++)
		if(ans[i]<min)
			min = ans[i];
	printf("%d\n",min);
	return 0;
}
