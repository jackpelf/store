#include<stdio.h>
int main()
{
	double ans;
	double n;
	while(scanf("%lf",&n) != EOF)
	{
		ans = (n*(n+1) / 2);
		printf("%.0lf\n",ans);
	}
	return 0;
}
