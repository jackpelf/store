#include<stdio.h>
#include<string.h>
int main()
{
	char p[1000] = "skdsjl\tlwwwwwwwwwwww\twerqwqqoppppp\tyyyyyy";
	printf("%s\n", strsep(p, '\t'));
	return 0;
}
