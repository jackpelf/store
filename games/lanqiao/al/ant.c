#include<stdio.h>
#include<string.h>
#define N 101
char map[N][N];
char d;
int main()
{
	int m,n,i,j;
	int x,y,c;
	scanf("%d %d", &m, &n);
	for(i=0; i<m; i++)
	{
		for(j=0; j<n; j++)
			scanf("%d", &map[i][j]);
	}
	scanf("%d %d %c %d", &x, &y, &d, &c);
	for(i=0; i<c; i++)
	{
		if(map[x][y] == 0)
		{
			switch(d)
			{
				case 'U':map[x][y] = 1; d = 'L'; y--; break;
				case 'D':map[x][y] = 1; d = 'R'; y++; break;
				case 'L':map[x][y] = 1; d = 'D'; x++; break;
				case 'R':map[x][y] = 1; d = 'U'; x--; break;
			}
		}
		else
		{
			switch(d)
			{
				case 'U':map[x][y] = 0; d = 'R'; y++; break;
				case 'D':map[x][y] = 0; d = 'L'; y--; break;
				case 'L':map[x][y] = 0; d = 'U'; x--; break;
				case 'R':map[x][y] = 0; d = 'D'; x++; break;
			}
		}
	}
	printf("%d %d\n", x, y);
	return 0;
}
