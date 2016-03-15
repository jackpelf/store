#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int ans = 0;
int main()
{
	int n;
	scanf("%d\n", &n);
	int i;
	int t,first;
	scanf("%d", &first);
	for(i=0; i<n-1; i++)
	{
		scanf("%d", &t);
		if(abs(t) < abs(first))
			if(t>0)
				ans ++;
		if(abs(t) > abs(first))
			if(t<0)
				ans ++;
	}
	printf("%d\n", ans+1);
	return 0;
}
