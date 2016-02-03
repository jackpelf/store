.section .text
.global _start
_start:

loop:
	ldrb r3, [r0]
	strb r3, [r1]
	subs r2, r2, #1
	bge loop

	bx lr
