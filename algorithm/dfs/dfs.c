#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char G[10][10];
char S[10];
int n,k,ans;


int dfs(int l, int num)
{
	int i;
	for(i=0; i<n; i++)
	{
		if(G[i][l]=='#' && S[i]==0)
		{
			if(num==k)
			{	
				ans++;
			}
			else
			{
				S[i]=1;
				for(int small=l+1; small<=n-k+num; small++)
				dfs(small, num+1);
				S[i]=0;
			}
		}
	}
}

int main()
{
	int i,j;
	while(scanf("%d%d\n", &n, &k))
	{
		ans = 0;
		memset(S, 0, sizeof(S));
		if (n==-1&&k==-1)
			break;
		for(i=0; i<n; i++)
		{
			for(j=0; j<n; j++)
			{
				scanf("%c", &G[i][j]);
			}
			getchar();
		}
		for(i=0;i<=n-k;i++)
			dfs(i,1);
		printf("%d\n",ans);
	}
}
