#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char visited[5000];
	int m,n,sig,i,j,k,count;
	scanf("%d", &m);
	for(k=0; k<m; k++)
	{
		scanf("%d", &n);
		memset(visited,0,n);
		sig = 2;
		count = n;
		while(1)
		{
			if(count <= 3 )
				break;
			j = 0;
			for(i = 0; i<n; i++)	//through one loop
			{
				if(visited[i])
					continue;
				if((j+1) % sig == 0)
				{
					count--;
					visited[i] = 1;
				}
				j++;
			}	
			if(sig == 2)
				sig = 3;
			else
				sig =2;
		}
		count = 0;
		for(i = 0; i<n; i++)
		{
			if(!visited[i])
				count++;
		}	
		j = 0;
		for(i = 0; i<n; i++)
		{
			if(!visited[i] )
			{
				j++;
				if(count == j)
					printf("%d",i+1);
				else
					printf("%d ",i+1);
			}
		}	
		printf("\n");
	}
}
