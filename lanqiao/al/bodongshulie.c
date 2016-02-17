#include<stdio.h>
#include<string.h>
long long ans = 0;
long long sum = 0;
long long s;
long long a,b,n;
long long start;
void dfs(long long now,int num)
{
	if (num == 1)
	{
		sum = sum + now;
		if(sum == s)
			ans ++;
		sum = sum - now;
	}
	else
	{
		sum = sum + now;
		dfs(now + a, num - 1);
		dfs(now - b, num - 1);
		sum = sum - now;
	}
}
int main()
{
	scanf("%ld%ld%ld%ld", &n, &s, &a, &b);	
	long long max = s/n + a*n;
	long long min = s/n - b*n;
	for(start = min; start < max; start++)
	{
		sum = 0;
		dfs(start, n);
	}
	printf("%d\n", ans % 100000007);
	return 0;
}
