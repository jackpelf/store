#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<map>
//poj 3026
using namespace std;
char g[100][100];//地图
int n,m;
int a[100][100];//如果有记录这个点对应的邻接矩阵的每一个
int move[][2]={{1,0},{-1,0},{0,1},{0,-1}};
int cost[110][110];//邻接矩阵
int t[100][100];//临时记录起点到各点之间的距离
void bfs(int sx,int sy)
{

    queue<pair<int,int> > q;
    while(!q.empty())
        q.pop();
    memset(t,-1,sizeof(t));
    t[sx][sy]=0;
    q.push(make_pair(sx,sy));
    while(!q.empty())
    {
        pair<int,int> now = q.front();
        q.pop();
        if(a[now.first][now.second]!=-1)		//如果有点
	{
	        cost[a[sx][sy]][a[now.first][now.second]] = t[now.first][now.second];	//从源点到目的点的距离
	        //printf("cost: %d\n", t[now.first][now.second]);
	}
        for(int i=0;i<4;i++)		//把四个方向都push进去
        {
            int tx=now.first+move[i][0];
            int ty=now.second+move[i][1];
            if(g[tx][ty]=='#' || t[tx][ty]!=-1)	//遍历过就不在遍历
                continue;
            t[tx][ty]=t[now.first][now.second]+1;
            q.push(make_pair(tx,ty));
        }
    }
}

const int INF=0x3f3f3f3f;
bool vis[110];//是否经历
int lowc[110];//到已知集合的最小权值
int Prim(int n)
{
	int ans=0;
	memset(vis,false,sizeof(vis));
	vis[0]=true;
	for(int i=0;i<n;i++)
		lowc[i]=cost[0][i];
	/*
	puts("--------------------------");
	for( int i=0; i< n; i++)
	{
		printf("%d\n",lowc[i]);
	}
	puts("--------------------------");
	*/
	for(int i=0;i<n-1;i++)
	{
		int minc=INF;
		int p=-1;
		for(int j=0;j<n;j++)		//把最小边标记
		{
			if(!vis[j] && minc>lowc[j])
			{
				minc=lowc[j];
				p=j;
			}
		}
//		printf("**********:%d\n", ans);
		if(minc==-1) return -1;
		ans+=minc;
		vis[p]=true;
		for(int j=0;j<n;j++)		//查找最小边
		{
			if(!vis[j]&&lowc[j]>cost[p][j])
			 lowc[j]=cost[p][j];
		}
	}
	return ans;
} 



int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&m,&n);
        gets(g[0]);
        memset(a,-1,sizeof(a));
        int tol=0;
        for(int i=0;i<n;i++)
        {
            gets(g[i]);
            for(int j=0;j<m;j++)
	    {
               if(g[i][j]=='A' || g[i][j]=='S')
                   a[i][j] = tol++;
	    }
        }
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(a[i][j]!=-1)
                    bfs(i,j);//生成邻接矩阵
        printf("%d\n",Prim(tol));//求最小生成树的权值和
    }
    return 0;
}
