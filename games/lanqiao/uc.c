#include<stdio.h>
#include<string.h>
int buf[11][11];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
char isv[10][10];
int sum=0;
int m,n;
int check(int nx, int ny, int now)
{
	if(nx < 1 || nx > n || ny < 1 || ny > m)
		return 0;
	if(isv[nx][ny] == 1)
		return 0;
	if(now + buf[nx][ny] > sum/2)
		return 0;
	return 1;
}
int dfs(int x, int y, int now)
{
	int tmp = now + buf[x][y];
	if(tmp == sum/2)
		return 1;
	else
	{
		int k;
		for(k=0; k<4; k++)
		{
			int nx = x + dx[k];
			int ny = y + dy[k];
			if(check(nx, ny, tmp))
			{
				isv[nx][ny] = 1;
				int res = dfs(nx, ny, tmp);
				if(res)
					return 1+res;
				isv[nx][ny] = 0;
			}
	
		}
	}
}
int main()
{
	int i,j;
	scanf("%d%d", &m, &n);
	for(i=1; i<=n; i++)
		for(j=1; j<=m; j++)
		{
			scanf("%d", &buf[i][j]);
			sum += buf[i][j];
		}
	printf("sum: %d\n", sum);
	if(sum % 2)
	{
		puts("0");
		return 0;
	}
	else
	{
		memset(isv, 0, sizeof(isv));
		printf("%d\n", dfs(1,1,0));
	}
	return 0;
}
