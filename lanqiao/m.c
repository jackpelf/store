#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int a[100000],tmp[100000];
int l[100000]  = {0};
int ans = 0;
void megearray(int s,int m,int e)
{
	int i = s,j = m;
	int c = s;
	while(i<m && j<=e)
	{
		if(a[i]>a[j])
		{
			l[c] += m-i+1;
			tmp[c++] = a[j++];
		}
		else
		{
			l[c] += j-m;
			tmp[c++] = a[i++];
		}
	}
	while(i<m)	
	{
		l[c] += m-i+1;
		tmp[c++] = a[i++];
		ans += m-i;
	}
	while(j<=e)
	{
		tmp[c++] = a[j++];
	}
	for(i=s; i<=e; i++)
		a[i] = tmp[i];
}
void Megesort(int s,int e)
{
	if(s<e)
	{
		Megesort(s, (s+e)/2);
		Megesort((s+e)/2+1, e);
		megearray(s, (s+e)/2, e);
	}
}
int main()
{
	int n;
	int i;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);
	Megesort(0,n-1);
	for(i=0; i<n; i++)
		ans += (l[i]*(l[i]+1))/2;
	printf("%d\n", ans);
	return 0;
}
