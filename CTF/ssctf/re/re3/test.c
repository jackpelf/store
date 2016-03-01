#include <stdio.h>
#include <stdlib.h>
int main ()
{
	int out,i;
	char buf[] = "g5c760c64E867618gGfG48GeF92C4f5e";
    do
    {
      int tmp = buf[i];
      int flag = 0;
      if ( tmp > '9' || tmp < '0' )
      {
        if ( tmp > 'z' || tmp < 'a' )
        {
          if ( tmp <= 'Z' && tmp >= 'A' )
            tmp -= 65;
        }
        else
        {
          tmp -= 97;
          flag = 1;
        }
        out = (23 + 5 * tmp) % 26 + ((23+ 5 * tmp) % 26 < 0 ? 26 : 0);
        if ( flag )
        {
          if ( flag == 1 )
            out = out + 97;
        }
        else
        {
          out = out + 65;
        }
        buf[i] = out;
      }
      ++i;
    }
    while ( i < 32 );
	puts(buf);
}
