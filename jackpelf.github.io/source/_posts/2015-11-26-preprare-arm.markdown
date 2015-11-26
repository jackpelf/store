---
layout: post
title: "preprare-arm"
date: 2015-11-26 23:49:57 +0800
comments: true
categories: 
---

###wireshark
过滤dhcp：bootp    
过滤一定ip.addr == 地址

###Rop skill
使用 _dl_runtime_resolve的gadget改变内存属性，进而执行shellcode  
__libc_csu_init()可以控制esi和edi

###windows exp
mona可以搜索gadget  
mona jmp -r 寄存器 -m 模块 可以查找指定模块使用指定寄存器的gadget

###虚拟机
基于虚拟机的代码混淆技术  
定义字节码  
实现虚拟机(寄存器.解释器)

###python httpserver
python -m SimpleHTTPServer 80  

###armgcc
arm-none-linux-gnueabi-gcc基于linux，使用glibc  
arm-none-eabi-gcc一般适合ARM7、Cortex-M,Cortex-R,使用newlib  
arm-eabi-gcc,Android ARM 编译器  
arm-linux-androideabi-gcc安卓编译器  

### arm -linux-gnueabi安装
下载arm-linux-gcc  
解压  
vi /etc/profile添加环境变量  

###android
android不使用glibc，ld为/system/bin/link  
可以静态链接或者  
-dynamic-linker=/system/lib/ld-linux.so.3


###解压

    tar 
    tar xvf
    gz2
    tar zxvf

###使用glibc
lib的存放目录arm-none-linux-gnueabi/lib  
mount改变system权限，写入libc.so.6  
mount -o remount,rw /dev/block/mtdblock3  /system  
编译时制定linker  
-dynamic-linker=/system/lib/ld-linux.so.3  

###动态库搜索路径
环境变量LD_LIBRARY_PATH  
/etc/ld.so.conf  
gcc制定  



