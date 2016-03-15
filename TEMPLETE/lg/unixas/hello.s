#	gcc -c hello.s
#	ld hello.o -o hello
#


.section .bss	#[xw]
ch:	.byte	1;
.section .rodata
msg:
   .ascii "Hello, world.\n"
 
.section .text
func:
   movl  $4,    %eax    # system call  
   movl  $1,    %ebx    # file descriptor 
   movl  $msg,  %ecx    # string address 
   movl  $14,   %edx    # string length 
   int   $0x80          # 
   ret

.globl _start
_start:
   call func
 
   movl  $1, %eax     #
   movl  $0, %ebx     # 
   int   $0x80        # 


