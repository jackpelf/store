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
node now;
node next;
//先遍历的步数少
int bfs()
{
	queue<node>q;
	now.num = n;
	now.path = 0;
	q.push(now);
	visited[now.num] = 1;
	while(!q.empty())
	{
		now = q.front();
		next = now;
		q.pop();
	//	cout<<"each"<<now.num<<" "<<now.path<<endl;
		for(int i=0; i<3; i++)
		{
			if(i==0)
				next.num = now.num+1;
			if(i==1)
				next.num = now.num-1;
			if(i==2)
				next.num = now.num*2;
			next.path = now.path+1;
			if(next.num == k)			//find
				return next.path;
			if(next.num<0||next.num>1000000)	//out of range
				continue;
			//cout<<t.num<<" "<<visited[t.num]<<endl;
			if(visited[next.num] == false)		//is visited
			{
				visited[next.num]=true;
				q.push(next);
			}
		}
		//同一时期push进的path相同,保证pop出来比较的最小
	}
	return 0;
}

//寻找最小的步数，采用bfs

int main()
{
	int ans;
	while(cin>>n>>k)
	{
		if(n == k)
			cout<<'0'<<endl;
		else if(n > k)
			cout<<(n-k)<<endl;
		else
		{
			memset(visited, false, sizeof(visited));
			ans = bfs();
			cout<<ans<<endl;
		}
	}
	return 0;
}
