#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned char bp[9]="123456789";
unsigned char store[9]="123456789";
int fact[]={1,1,2,6,24,120,720,5040,40320};
int permutation()
{
        int c;
        char buf[10]={0};
        int i;
        int m,lm;
        for(lm=0;lm<362880;lm++)
        {
                m=lm;
                c=0;
                for(i=0;i<9;i++)
                {
                        int t=m/fact[8-i];
                        int j=0;
                        int jc=0;
                        for(j=0;j<10;j++)
                        {
                                if(store[j]!=255)
                                {
                                        if(t==jc)
                                        {
                                                buf[c++]=store[j];
                                                store[j]=255;
                                                break;
                                        }
                                        jc++;
                                }
                        }
                        m=m%fact[8-i];
                }
                puts(buf);
                strncpy(store,bp,9);
        }

}
int main()
{
        permutation();
        return 0;
}
