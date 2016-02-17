#include<stdio.h>
#include<stdlib.h>
long long ans = 0;
int main()
{
	int n,k,T;
	int c,i;
	scanf("%d %d %d", &n, &k, &T);
	int buf[1000001];
	int tmp = k+5;
	c = 1;
	i = 1;
	while(tmp)
	{
		buf[c-1] = i;
		i = (i+c) % k;
		c++;
		tmp -- ;
	}
	i = 0;
	while(T)
	{
		ans += buf[i];
		i = (i+n) % k;
		T--;
	}
	printf("%I64d\n", ans);
	return 0;
}
