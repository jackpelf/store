#include<stdio.h>
#include<string.h>
int main()
{
	int i;
	int s[20];
	s[0] = "103066";
	s[1] = "78yn";
	s[2] = "91";
	s[3] = "jk@O";
	s[4] = "w0%3";
	s[5] = "okJni";
	s[6] = "32tP";
	s[7] = "pYn";
	s[8] = "oty3e";
	s[9] = "ss";
	s[10] = "whw3";
	s[11] = "Gh$";
	s[12] = "ju3t";
	s[13] = "g986";
	s[14] = "rTp0";
	s[15] = "J)g";
	s[16] = "a";
	s[17] = "pLoKm7";
	s[18] = "0o7";
	qsort(s, 19, 4, strcmp);
	for(i=0; i<19; i++)
		puts(s[i]);
	return 0;
}
