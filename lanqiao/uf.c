#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int store[1000];
int start[1000];
char isv[1000];
int n,m;
int c;		//0 you 1 me
int flag; 	//for each choice if one case don't meet set 0
int depth;
int dfs(int last)
{
	depth++;
	int t;
	for(t=0; t<depth; t++)
		printf(" ");
	printf("%d\n", last);
	c = !c;
	int i;
	int nomorechoice = 1;
	int allv = 1;
	for(i=0; i<n; i++)
	{
		if(isv[i] == 0)
		{
			allv = 0;
			if(store[i] % last == 0 || last % store[i] == 0)
			{
				nomorechoice = 0;
				isv[i] = 1;
				dfs(store[i]);
				isv[i] = 0;
			}
		}
	}
	depth--;
	if(nomorechoice == 1 )		//can't find
	{
		if(allv == 1)
		{
			return 0;
		}
		if( c == 0 )
			return 0;
		if( c == 1 )
			flag = 0;
	}
}
int main()
{
	int i=0;
	while(1)
	{
		scanf("%d", &store[i++]);
		if(getchar() == '\n')
			break;
	}
	n = i;
	i=0;
	while(1)
	{
		scanf("%d", &start[i++]);
		if(getchar() == '\n')
			break;
	}
	m = i;
	for(i=0; i<m; i++)
	{
		printf("start[i]: %d\n", start[i]);
		memset(isv, 0, sizeof(isv));
		int j;
		for(j=0; j<n; j++)
			if(start[i] == store[j])
			{
				isv[j] = 1;
				break;
			}
		c = 1;
		flag = 1;
		depth = 0;
		dfs(start[i]);
		if(flag == 1)
		{
			printf("%d\n", start[i]);
			puts("found");
			break;
		}
	}
	return 0;
}
