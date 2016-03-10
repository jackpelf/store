#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
char isv[362880] = {0};
int queue[362880*2];
int next[]={-1,1,3,-3};
int start,end;
int fact[9]={1,1,2,6,24,120,720,5040,40320};
int po[9]={1,10,100,1000,10000,100000,1000000,10000000,100000000};
int kt(int num)
{
	int i;
	int ans=0;
	int store[9] = {1,2,3,4,5,6,7,8,9};
	for(i=8; i>=0; i--)
	{
		int j;
		int c=0;
		int w = (num/po[i]) % 10;
		for(j=0; j<9; j++)
			if(store[j]!=0)
			{
				if(store[j] == w)
				{
					ans += fact[i]*c;
					store[j]=0;
					break;
				}
				c++;
			}
	}
	return ans;
		
}
int bfs(int one)
{
	int p=-1,q=-1;
	queue[++q] = one; 
	queue[++q] = 0; 
	while(p<=q)
	{
		int ti=queue[++p];
		int tl=queue[++p];
		printf("%d\n",ti);
		int cpti = ti;
		int i=8;
		int old,new;
		while(ti)
		{
			if(ti%10 == 9)
			{
				old = i;
				break;
			}
			i--;
			ti/=10;
		}
		for(i=0; i<4; i++)
		{
			if(old % 3==0 && next[i]==-1 || old%3==2 && next[i]==1)
				continue;
			if(old+next[i] > 8 || old+next[i] < 0)
				continue;
			new = old+next[i];
			int tmp=0;
			int j=0;
			ti=cpti;
			int per=ti/((8-new)*10) % 10;
			for(j=0; j<9; j++)
			{
				if(8-j == new)
					tmp += (per)*po[j];
				else if(8-j == old)
					tmp += 9*po[j];
				else
					tmp += ((ti)/po[j]  % 10)*po[j];
			}
			printf("tmp: %d\n", tmp);
			if(tmp==end)
			{
				puts("found");
				return 0;
			}
			int index = kt(tmp);
			if(isv[index])
				continue;
			isv[index] = 1;
			queue[++q]=tmp;
			queue[++q]=tl+1;
		}
	}
}
			
int main()
{
	char buf[10];
	scanf("%s", buf);
	*strchr(buf, '.') = '9';
	start=atoi(buf);
	scanf("%s", buf);
	*strchr(buf, '.') = '9';
	end=atoi(buf);
	bfs(start);
	return 0;
}
