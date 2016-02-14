/*
gcc -o elf elf.c
*/
#include<stdio.h>
#include<math.h>
int main(int argc, char **argv)
{

	puts("argv test");
	printf("argc: %d\n", argc);
	if(argc != 1)
	{
		printf("argv[1]: ");
		puts(argv[1]);
	}
	puts("\nprintf test");
	int i = 233;
	float f = 233.2333333;
	printf("hello world\n");
	printf("integer: %d, float: %f", i, f);

	puts("\nscanf test(input some string)");
	FILE *fp;
	char buf[20];
	scanf("%s", buf);
	puts(buf);

	puts("\nfile test");
	fp = fopen("text", "r");
	fread(buf, 10, 1, fp);
	puts(buf);
	fclose(fp);
	
	puts("\nmath test");
	printf("sin: %lf\n", sin(23));
	printf("cos: %lf\n", cos(23));
	return 0;
}
