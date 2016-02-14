#include<stdio.h>
#include<string.h>
int main()
{
    char buf[20] = "hello";
    write(1, buf, 11);
    int res = getc(1);
    printf("______\n%d\n_______\n", res);
    return 0;
}
