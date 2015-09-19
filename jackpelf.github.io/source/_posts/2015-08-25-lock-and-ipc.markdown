---
layout: post
title: "lock &amp; ipc"
date: 2015-08-25 20:54:31 -0700
comments: true
categories: 
---

##0x00 锁
-原子操作：  
最简单的锁操作，可以不中断地原子执行  
-自旋锁：  
用于短期保护某段代码，防止其他处理器访问  
-信号量：  
等待信号量释放时，内核进入睡眠状态，直至被唤醒。互斥量是信号量的特例，互斥量保护的临界区，每次只能有一个用户进入。  
-读者/写者锁：  
这些锁会区分数据结构的两种不同类型的访问。任意数目的处理器都可以并发读，但只有一个处理器能进行写方法。  

##0x00 整数原子操作

内核定义了atomic_t数据类型  
为SMP系统提供了local_t数据类型  

	原子操作
	atomic_read
	atomic_set
	atomic_add
	atomic_add_return
	atomic_sub
	atomic_sub_return
	......
##0x01 自旋锁
自旋锁通过spinlock_t数据结构实现，基本上可以使用spin_lock和spin_unlock操纵，还有其他一些自旋操作，spin_lock_irqsave不仅获得自旋锁，还停用本地CPU中断  
用法:
	spinlock_t lock = SPIN_LOCK_UNLOCKED
	..
	spin_lock(&lock);
	/* 临界区 */
	spin_unlock(&lock);
(1) 如果内核中其他地方尚未获得lock, 则由当前处理器获取，其他处理器不能再进入lock保护的代码范围 
(2) 如果lock已经有另一个处理器获得，spin_lock进入一个无限循环，重复地检查lock是否已经由spin_unlock释放，如果已经释放，则获得lock,并进入临界区  

在单处理器系统上，自旋锁兴义为空操作，因为不存在几个cpu同时进入临界区的情况。但如果启用了内核抢占，这种说法就不适用了。如果内核在临界区被中断，而此时另一个进程进入临界区，这与SMP系统上是等效的。    

##0x02 信号量
	struct semaphore
	{
		atomic_t count;
		int sleepers;
		wait_queue_head_t wait;
	};

+count指定了可以同时处于信号量保护的临界区的进程数目，count == 1为互斥信号量  
+sleepers指定了等待允许进入临界区的进程的数目  
+wait用于实现一个队列，保存在该信号量上睡眠的task_struct

信号量用于保护更长的临界区以防止并行访问。  

	count = 1;
	DECLARE_MUTEX(mutex)
	...
	down(&mutex)
	/* 临界区 */
	up(&mutex)

##0x03 读者/写者锁

读者/写者自旋锁定义为rwlock_t数据类型。
+进程对临界区进行读访问时，在进入和离开时需要分别执行read_lock和read_unlock.内核会允许任意数目的读进程并发访问临界区.  
+write_lock和write_unlock用于写访问。内核保证只有一个写进程（此时没有读进程）能够处于临界区中。  

读写信号量的用法类似。所用的数据结构是struct rw_semaphore, down_read和up_read用于获取对临界区的读访问，写访问借助于down_write和up_write进行。


##0x04 互斥量

1.经典的互斥量
	struct mutex
	{
		atomic_t	count;
		spinlock_t 	wait_lock;
		struct list_head	wait_list;
	};

如果互斥量未锁定，则count 为1.锁定分为两种情况，如果只有一个进程在使用互斥量,则count设置为0,。如果互斥量被锁定，而且有进程在等待互斥量解锁，则count为负值。  
+静态互斥量可以使用DEFINE_MUTEX产生  
+mutex_init在运行时动态初始化一个新的互斥量  

mutex_lock和mutex_unlock分别用于锁定和解锁互斥量。  

2.实时互斥量  
实时互斥量实现优先级继承，可以解决优先级优先级反转的影响  

	struct rt_mutex
	{
		spinlock_t wait_lock;
		struct plist_head wait_list;
		struct task_struct *owner;
	};
互斥量的所有者通过owner指定，wait_lock提供实际的保护。所有等待的进程都在wait_list中排队,与普通互斥量相比，决定性的改变是等待列表中进程按优先级排序。  
rt_mutex_init  
rt_mutex_lock  
rt_mutex_unlock  
_mutex_trylock  

##0x05 RCU机制  

	rcu_read_lock();

	p = rcu_dereference(ptr);
	if (p != NULL)
	{
		function(p);
	}

	rcu_read_unlock();

*被反引用的指针不能在r_read_lock()和rcu_read_unlock()保护的代码范围之外引用，也不能用于写访问*

如果必须修改ptr指向的对象，则需要使用rcu_assign_pointer  

2.链表操作

RCU能保护的，不仅仅是一般的指针，内核也提供了标准函数，使得能通过RCU机制保护双链表，这是RCU机制在内和内部最重要的应用。此外，由struct hlist_head和struct hlist_node组成的散列表也可以通过RCU保护。  

- list_add_rcu将新的链表元素new添加到表头为head的链表头部，而list_add_tail_rcu将其添加到链表尾部。  
- list_replace_rcu替换链表元素
- list_del_rcu从链表删除链表元素


##0x06 大内核锁
可以锁定整个内核，确保没有处理器在核心态并行运行，即BKL

##0x07 per_CPU计数器

	struct percpu_counter
	{
		spinlock_t lock; 	//自旋锁
		long count;		//计数器的准确值
		long *counters;		//
	};

下列函数可以修改per-CPU计数器

	percpu_counter_add
	percpu_counter_dec
	...


##0x08 ipc

信号量  
消息队列  
共享内存  
管道
套接字

##0x09 信号量

使用semget系统调用可以分配一个信号量集合，它需要一下参数：魔数（SEMKEY），集合中信号量的数目,所需访问的权限  
然后使用semctl系统调用将信号量集合中唯一的信号量的值初始化为1。
up和down操作修改信号量，使用semop系统调用进行

##0x0A 消息队列

产生消息并写到队列的进程成为发送者，而一个或多个其他进程成为接收者。各个消息包含消息正文和一个正数，接收者可以根据数字检索消息。  
	struct msg_queue
	{
		struct kern_ipc_per	q_perm;
		time_t 			q_stime;	//上次调用msgsnd发送时间
		time_t			q_rtime;	//msgrcv接收时间
		time_t 			q_ctime;	//上次修改时间
		unsigned long 		q_cbytes;	//当前字节数目
		unsigned long		q_qnum;		//消息数目
		unsigned long		q_qbytes;	//队列上最大字节数目
		pid_t 			q_lspid;	//上次调用msgsnd的pid
		pid_t			q_lrpid;	//上次接收的pid
		struct list_head	q_messages;	//消息本身
		struct list_head	q_receivers;	//睡眠的接收者
		struct list_head	q_senders;	//发送者
	}

消息实例

	struct msg_msg
	{
		struct list_head m_list;
		long m_type;			//消息类型
		int m_te;			//消息征文长度
		struct	msg_msgseg* next;	//接下来实际的消息
	};


##0x0B	共享内存
应用程序请求的IPC对象，可以通过魔数和命名空间内部的ID访问;  

##0x0C 信号

kill命令根据PID向进程发送信号，信号通过-s sig指定，是一个正整数，最大长度取决于处理器类型。  
过去32为系统最多支持32个信号  
进程必须设置处理程序历程来处理信号。(但有几个信号行为无法修改，如SIGKILL），如果没有指定，内核则使用默认的处理程序实现。
进程可以决定阻塞特定的信号。  
SIGKILL信号无法阻塞，也不能特定于进程的处理程序处理。 
SIGTERM可以通过用户定义的信号处理程序处理。  
init进程属于特例，内核会虎落发送的SIGKILL信号  

-发送信号
kill和tkill分别向进程组或单个进程发送信号  
在find_task_by_vpid找到目标进程的task_struct之后，内核将检查进程是否有发送信号所需权限的工作委托给check_kill_permission

	sys_tkill
	   |
	   --->do_tkill
		|
		|---->find_task_by_vpid
		|
		|---->check_kill_permission
		|
		|---->specific_send_sig_info
				|
				|------>sig_ignored?------>取消处理
				|
				|------->send_signal
				|
				|------->signal_wake_up
			
如果信号被阻塞（用sig_ignored检查），则立即放弃处理，以免又浪费时间  
send_signal产生一个新的sigqueue实例（使用sigqueue_cachep缓存），其中填充了信号数据，并添加到目标进程的sigpending链表  
如果信号发送成功，没有阻塞，就可以用signal_wake_up唤醒进程，使得调度器可以选择该进程运行。此外还设置了TIF_SIGPENDING标志，向内核表明必须将信号传送到该进程。  

-处理信号队列  

处理是在用汇编语言代码中发起的，因此实现特定于体系结构,最终的效果就是调用do_signal函数   
get_signal_to_deliver收集了与需要传送的下一个信号有关的所有信息,它也从特定于进程的带觉信号链表中删除该信号  
handle_signal操作进程在用户状态的栈，这种复杂的方法是必要的，因为处理程序函数不能再核心态执行

		  do_signal
		      |					  sys_sigreturn 
	核心态   handle_signal    |			^		|
	--------------------------|---------------------|---------------|---------------------------
	用户态                    V			|		V
					信号处理程序 		        	程序继续处理

##0x0D	管道

通过shell产生管道时，总有一个读进程和一个写进程，应用程序必须调用pipe系统调用产生管道，该调用返回两个文件描述符，分别用于管道的两端。   
管道是进程地址空间的数据对象，在fork和clone复制时同样会被复制。

##0x0E 套接字

套接字对象在内核中初始化也返回一个文件描述符，因此可以像普通文件一样处理  
套接字可以双向使用，还可以通过网络连接的远程系统通信。

