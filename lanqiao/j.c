#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	int buf[1000000];
	int i,j;
	j = 1;
	int c = 2;
	for(i=1; i<1000000; i++)
	{
		if(i % 2 == 0)
			continue;
		buf[j++] = i;
	}
	int max = 500000;
	while(1)
	{
		j = 1;
		for(i=1; i<max; i++)
		{
			if(i % buf[c] == 0)
				continue;
			buf[j++] = buf[i];
		}
		max = (float)(buf[c] - 1) / (float)buf[c] * (float)max;
		c++;
		if(c > 1000)
			break;
	}
	int a,b;
	scanf("%d%d", &a, &b);
	int ans = 0;
	for(i=1; i<max; i++)
		if(buf[i] > a && buf[i] <b)
			ans++;
	printf("%d\n", ans);
	return 0;
}
