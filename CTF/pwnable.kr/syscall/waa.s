#	gcc -c hello.s
#	ld hello.o -o hello
#

.section .bss
.section .rodata
.section .text
.globl _start
_start:
#write
loop:	ldrb r3, [r0], #1
	strb r3, [r1], #1
	sub r2, r2, #1
	bge loop
	bx lr
