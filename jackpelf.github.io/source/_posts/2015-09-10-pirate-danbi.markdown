---
layout: post
title: "pirate_danbi"
date: 2015-09-10 00:57:25 +0800
comments: true
categories: 
---
###0x00 elf  
codegate 2015 pirate_danbi  
###0x01 分析程序流程  
main  
储存REMOTE_HOST在s_bss,tmp_bss  
system_sh_tmp@bss会执行tmp@bss  
if 0x6030EC == 1  
0x6030EC is set by 0x4012B0(f4)    
if YO_DANBI_CREW_IN_THE_HOUSE == 0x603100  
0x400EDB is set by 0x400EDB(f1_1)  
piratekey store in store_pira_main@mainstack + 4  
输入格式  
ptr    v11 v12  
cmd bigendianlength  
then read length byte to s@main  
  
f1_1(store_pirate@main, s@main, length)  
XOR key with last block os the 密文  
last block is the key  
最后是否按照PKCS#5 padding  
除了最后一块,异或这一个和下一个密文的block并加上pirate_key  
						   -----------
						   |         | 
	-------   -------   -------   -------   -------      | 
	  |  xor   | |  xor   | |  xor   | |  xor   |        | xor piratekey 
	  |--------| |--------| |--------| |--------|        | 
	  V          V          V          V                 | 
	d_bss       d_bss      d_bss      d_bss    d_bss <----
  
  
  
###0x02how to use  
use f1 set 006030F0 md_byf3f1 = 1  
use f2 BZopen file f3 decompress * 1000 times to brute forcing piratekey  
set 0603100 ; char will_be_cmpedtoYODANBI[] to YO_DANBI_CREW_IN_THE_HOUSE.  
f4 will set 006030EC setbyf4 to 1  
use f5 to excute tmp@bss  
  
  
  
###0x03 prepare  
  
ltrace ./pirate_danbi  
export REMOTE_HOST=iiiiiiiiiiiiiiiiiiiii  
  
  
