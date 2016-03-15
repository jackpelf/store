#include<stdio.h>
#include<math.h>
#define MAX 100
int main()
{
	int n, start;
	scanf("%d", &n);
	scanf("%d", &start);
	int i;
	int ans = 1;
	for(i=1; i<n; i++)
	{
		int t;
		scanf("%d", &t);
		if(abs(t) < abs(start) && t > 0)
		{
			ans ++;
		}
		else if(abs(t) > abs(start) && t< 0)
		{
			ans ++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
	
		
	
