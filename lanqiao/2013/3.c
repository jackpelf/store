#include<stdio.h>
long long ans = 0;
void dfs(int i, int j)
{
	if(i == 3 && j == 4)
		ans++;
	else
	{
		if(i<3)
			dfs(i+1, j);
		if(j<4)
			dfs(i, j+1);
	}
}
int main()
{
	dfs(0, 0);
	printf("%ld\n", ans);
	return 0;
}
