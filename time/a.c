#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
	FILE *fp = fopen("database", "a");
	if(argc == 1)
	{
		time_t timer = time(NULL);
		fseek(fp, SEEK_END, 0);
		fprintf(fp, "%s", ctime(&timer));
		printf("%s", ctime(&timer));
		fclose(fp);
	}	
	
}
