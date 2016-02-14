#gdb bt -x debug.cmd
set logging file out.txt
set logging on
b *0x87b0
r
c
while 1
	i r r3
	x/wd $sp + 0x10
	c
end
q
