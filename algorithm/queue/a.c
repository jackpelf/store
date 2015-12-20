#include<stdio.h>
#include<string.h>
int main()
{
	int i,d,w,s,count,n;
	char visited[65];
	char names[65][16];
	memset(visited, 0, sizeof(visited));
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%s",names[i]);
	scanf("%d,%d", &w, &s);
	count = n;
	i = w - 1;
	d = 0;
	while(1)
	{	
		if(visited[i])
		{
			i = (i+1) % n;
			continue;
		}
		d++;
		if(d == s)
		{
			count--;
			puts(names[i]);
			visited[i] = 1;
			d = 0;
		}
		i = (i+1) % n;
		if(!count)
			break;
	}
	return 0;
}
