#include<stdio.h>
int buf[50000];
int ans=0;
int min(int i, int j)
{
	int t;
	int m;
	m = 0x7ffffff;
	for(t = i; t<=j; t++)
		if(m > buf[t])
			m = buf[t];
	return m;
}
int max(int i, int j)
{
	int t;
	int m;
	m = buf[i];
	for(t = i+1; t<=j; t++)
		if(m < buf[t])
			m = buf[t];
	return m;
}
int main()
{
	int n;
	scanf("%d", &n);
	int i,j;
	for(i=0; i<n; i++)
		scanf("%d", &buf[i]);
	int ma = 0;
	int mi = 0x7fffffff;
	int mai=0;
	int mii=0;
	for(i=0; i<n; i++)
	{
		ma = 1;
		mi = 0x7fffffff;
		for(j=i; j<n; j++)
		{
			if(ma < buf[j])
				ma = buf[j];
			if(mi > buf[j])
				mi = buf[j];
			if( (ma - mi) == (j-i))
			{
				ans ++;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
