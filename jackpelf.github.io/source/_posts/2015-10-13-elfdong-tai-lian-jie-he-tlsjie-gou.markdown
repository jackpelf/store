---  
layout: post  
title: "elf动态连接和tls结构"  
date: 2015-10-13 14:51:03 +0800  
comments: true  
categories:   
---  
  
###x000 tls  
struct pthread定义在  
nptl/descr.h  
  
tls结构  
  
	struct pthread  
	{  
		typedef struct  
		{  
		  void *tcb;        /* Pointer to the TCB.  Not necessarily the  
			       thread descriptor used by libpthread.  */  
		  dtv_t *dtv;  
		  void *self;       /* Pointer to the thread descriptor.  */  
		  int multiple_threads;  
		//SYSINFO_OFFSET也就是他的偏移。  
		  uintptr_t sysinfo;  
		  uintptr_t stack_guard;  
		  uintptr_t pointer_guard;  
		  int gscope_flag;  
		#ifndef __ASSUME_PRIVATE_FUTEX  
		  int private_futex;  
		#else  
		  int __unused1;  
		#endif  
		  /* Reservation of some values for the TM ABI.  */  
		  void *__private_tm[5];  
		} tcbhead_t;  
		...  
	}  
  
###0x01 elf 动态连接  
elf文件使用PIC技术使代码和数据的引用与地址无关，程序可以被加载到地址空间的任意位置。  
PIC代码中的跳转和分支指令不使用绝对地址。  
PIC在ELF可执行镜像的数据段中建立一个存放全局变量的全局偏移量表GOT  
对于模块外部引用的 全局变量和全局函数，用GOT表向的内容作为地址来间接寻址。  
对于本模块内的静态变量和函数，用GOT表的首地址作为一个基准，用相对于该基准的偏移量来引用。  
对于PIC代码，代码段内部不存在重定位项，实际的重定位项只是数据段的GOT表内。  
共享目标文件中的重定位类型有R_386_RELATIVE,R_386_GLOB_DAT,R_386_JMP_SLOT,用于动态连接器加载映射共享库或模块运行时候指针类型的静态数据、全局变量符号地址和全局函数符号地址.  
动态连接器在装载映射共享库时在GOT设置两个特殊值  
GOT[1]被设置动态库映射信息数据结构link_map的地址，GOT[2]设置动态连接器符号解析函数的地址_dl_runtime_resolve  
类型为PT_DYNAMIC的段是一个非常重要的段，他是一个结构数组，给出动态连接的所有管理信息。  
每条结构包含一个类型字段d_tag和一个虚拟地址d_ptr或整数值d_val的联合体d_un  
可执行文件和共享目标文件中主要的动态想有DT_NEEDED动态库依赖表，DT_PLTGOT全局偏移表，DT_HASH哈希表，DT_SYMTAB符号表,DT_STRTAB字符串表,DT_REL重定位表，DT_JMPREL与过程连接表对应的重定位表  
linux用一个全局的库映射信息结构link_map链表来管理和控制所有动态库的加载，动态库的加载过程是映射库文件到内存，填充库映射信息结构到链表的过程  
link_map使用双向连接l_next和l_prev连接进程中所有加载的共享库  
  
查找符号先从GOT[1]读取link_map节点地址，然后沿着link-map进行搜索  
动态库的加载映射过程  
1，调用mmap对动态库所有PT_LOAD可加载段进行整体映射  
动态连接器处理共享库的PT_DYNAMIC动态段，将各项动态连接信息包括哈希表、符号表、字符串表、重定位表、PLT重定位项表填写到link_map的l_info数组结构中  
由于映射的地址和指定的虚拟地址不同，还要对动态库及其依赖库进行重定位。  
设置动态库第一个和第二个GOT表项  
对动态库的所有重定位项进行重定位，在重定位项指定的偏移地址处加上修正值l_addr，动态项DT_REL给出了重定位表的地址，DT_RELSZ给出重定位项的数目  
符号解析  
第一次调用函数时，由PLT表跳转到GOT[2]设置的入口_dl_runtime_resolve,执行具体解析工作的fixup函数，在跳入栈上已压入参数：1，要解析的符号在DT_JMPREL重定位表中的偏移，间接指明要解析到那个GOT项去，2，动态链接库link_map指针  
fixup遍历link_map链表上的每个库节点，查找要解析的符号，先根据reloc_offset在本运行模块内查找要解析的符号名称；根据DT_JMPREL段的段内偏移reloc_offset找到要解析符号的重定位项结构信息reloc,再根据reloc->r_info找到相应的符号表和字符串表的索引。  
  
###0x02 线程函数  
把一个能被多个线程同时访问，且函数输出数据不会因为线程访问顺序的不同而不同的函数叫做线程安全函数  
再调用线程不安全函数时，必须要加锁或串行的执行  
线程特定数据允许一个函数为每个线程保留一份私有数据  
pthread_key_create()，所创建的 key 都是所有线程可以访问的，但各个线程可以根据自己的需要往 key 中填入不同的值，相当于提供了一个同名而不同值的全局变量  
  
