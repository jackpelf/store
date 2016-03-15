#include<stdio.h>
#include<string.h>
int buf[100][100];
int dx[] = {0, 1};
int dy[] = {1, 0};
int m,n,k;
long long ans = 0;
int dfs(int x, int y, int max, int num)
{
	//printf("%d %d %d %d\n",x,y,max,num);
	if(x == n && y == m && num == k)
	{
		ans ++;
		ans %= 1000000007;
		return 0;
	}
	int i;
	for(i=0; i<2; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(nx > n || ny > m)
			continue;
		if(max < buf[nx][ny])
			dfs(nx, ny, buf[nx][ny], num+1);	//take
		dfs(nx, ny, max, num);	//not take
	}
}
int main()
{
	int i,j;
	scanf("%d%d%d", &n, &m, &k);
	for(i=1; i<=n; i++)
		for(j=1; j<=m; j++)
		{
			scanf("%d", &buf[i][j]);
		}
	dfs(1, 1, buf[1][1], 1);
	dfs(1, 1, 0, 0);
	printf("%ld\n", ans );
	return 0;
}
