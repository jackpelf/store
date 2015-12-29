.section .rodata
msg:
   .ascii "Hello, world.\n"
 
.section .text
func:
   movl  $4,    %eax    # system call  系统调用号(sys_write)
   movl  $1,    %ebx    # file descriptor 参数一:文件描述符(stdout)
   movl  $msg,  %ecx    # string address  参数二:要显示的字符串
   movl  $14,   %edx    # string length  参数三:字符串长度
   int   $0x80          # 调用内核功能
   ret

.globl _start
_start:
   call func
 
   movl  $1, %eax     # 系统调用号(sys_exit)
   movl  $0, %ebx     # 参数一:退出代码
   int   $0x80        # 调用内核功能
