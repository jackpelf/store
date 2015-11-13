#include <stdlib.h>  
#include <stdio.h>  
#include <malloc.h>  
#include <string.h>  
#include <pthread.h>  
int main(int argc, char **argv)  
{  
	long long a=10, b = 0;  
	int *addr ;
	addr = malloc(234234232);
        printf("b:%p\n", b);  
        asm volatile(
		"mov rax,fs:[0];"  
                :"=a"(b)        
        );  
  
        printf("malloc:%p\n", addr);  
        printf("b:%p\n", b);  
        printf("ok\n");  
//	addr = 0x0007ffff7bb4000;
	addr = 0x0007ffff7bb8000;
	*addr = 3;
	sleep(322342);
}  
