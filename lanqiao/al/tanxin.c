/*
2+4+5 = 11
*oo*o**
ooooooo

3
ooooo**
ooooooo

ooo****
ooooooo

ooo*oo*
ooooooo

ooo*o*o
ooooooo

ooo**oo
ooooooo

ooooooo
ooooooo

*/

#include<stdio.h>
#include<string.h>
char a[1000];
char b[1000];
char diff[1000];
int main()
{
	scanf("%s%s", a, b);
	int n = strlen(a);
	int i;
	for(i=0; i<n; i++)
		if(a[i] != b[i])
			diff[i] = 1;
	int ans = 0;
	int flag = -1;
	for(i=0; i<n; i++)
		if(diff[i] == 1)
		{
			if(flag == -1)
			{
				flag = i;
			}
			else
			{
				ans += i - flag;
				flag = -1;
			}
		}
	printf("%d\n", ans);
	return 0;
}
