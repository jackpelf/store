#include <iostream>
using namespace std;
int main()
{
    int i,j,temp;
    for (i=0;i<=1000000000;i++)
    {
        temp=i;
        for (j=9;j>1;j--)
        {
            if (temp % j == 0)
            {
                temp=temp/10;
                continue;
            }
            else
            {
                break;
            }
        }
        if (j==1)
        {
            cout<<i<<endl;
         } 
    }
 }
