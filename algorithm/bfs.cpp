#include<iostream>
#include<string.h>
#include<queue>
using namespace std;

bool visited[1000000];
struct node{
	int num;
	int path;
};
int n,k;
//先遍历的步数少
int bfs()
{
	queue<node>q;
	node popedtmp;
	node t;
	popedtmp.num = n;
	popedtmp.path = 0;
	q.push(popedtmp);
	while(!q.empty())
	{
		popedtmp = q.front();
		t = popedtmp;
		q.pop();
		for(int i=0; i<3; i++)
		{
			if(i==0)
				t.num = popedtmp.num+1;
			if(i==1)
				t.num = popedtmp.num-1;
			if(i==2)
				t.num = popedtmp.num*2;
			t.path = popedtmp.path+1;
			if(t.num == k)			//find
				return t.path;
			if(t.num<0||t.num>1000000)	//out of range
				continue;
			if(visited[t.num] == false)		//is visited
			{
				visited[t.num]==true;
				q.push(t);
			}
				//同一时期push进的path相同
		}
	}
	return 0;
}

int main()
{
	int ans;
	while(cin>>n>>k)
	{
		memset(visited, false, sizeof(visited));
		ans = bfs();
		cout<<ans<<endl;
	}
	return 0;
}
