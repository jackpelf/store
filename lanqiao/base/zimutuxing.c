#include<stdio.h>
int main()
{
	char map[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int n,m;
	int i;
	scanf("%d%d", &n, &m);
	for(i=0; i<n; i++)
	{
		int t;
		for(t=i; t>0; t--)
			putchar(map[t]);
		for(t=0; t<m-i; t++)
			putchar(map[t]);
		putchar('\n');
	}
	return 0;
}
