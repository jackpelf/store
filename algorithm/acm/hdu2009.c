#include<stdio.h>
#include<math.h>

int main()
{
	int n,m;
	double t,ans;
	while(scanf("%d %d",&n,&m) != EOF)
	{
		ans = 0;
		t = n;
		while(m)
		{
			ans += t;
			t = sqrt(t);
			m --;
		}
		printf("%.2f\n", ans);
		
	}
	return 0;
}

