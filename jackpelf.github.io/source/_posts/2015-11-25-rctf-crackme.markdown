---
layout: post
title: "rctf-crackme"
date: 2015-11-25 23:45:59 +0800
comments: true
categories: 
---


###0x00 analysis


    .text:00401468 callapi         proc near               ; CODE XREF: _main+19p
    .text:00401468                                         ; _main+43p ...
    .text:00401468                 pop     ebx
    .text:00401469                 pop     esi
    .text:0040146A                 call    esi
    .text:0040146C                 push    ebx
    .text:0040146D                 retn
    .text:0040146D callapi         endp ; sp-analysis failed
    .text:0040146D
    .text:0040146E
    .text:0040146E ; =============== S U B R O U T I N E =======================================
    .text:0040146E
    .text:0040146E
    .text:0040146E pass2opcode     proc near               ; CODE XREF: _main+Cp
    .text:0040146E                                         ; _main+36p ...
    .text:0040146E                 pop     eax
    .text:0040146F                 add     eax, 2
    .text:00401472                 push    eax
    .text:00401473                 retn
    .text:00401473 pass2opcode     endp
    .text:00401473

反调试代码

获取模块并把地址存在栈上  
获取文件路径并存在栈上  
打开这个文件  
读入一部分数据（估计是size)
malloc一段空间，从文件中读入，并于0x7异或,virtualfree这段空间
virtualalloc一段空间，并把408044的地址处复制到这段空间，
再跳到这段空间
这段空间把malloc的数据复制到0x400000
又是一个upx加壳的exe，使用动态调试法脱壳
使用esp定律，在pushad处设置硬件断点，遇到循环按f4，可以手动脱壳
使用_filbuf输入
401020--hex化
401080
再次hex
生成table

``` C
      l = 0;
      table2[0] = hex1[0];
      table1[0] = -1;
      table3[0] = -1;
      for ( i = 1; i < 4 * j; ++i )                
      {
        ++l;
        table1[3 * l] = -1;
        table3[3 * l] = -1;
        table2[12 * l] = hex1[i];
        sub_401160(0, l);
      }
```

使用reorder函数置换

``` C
int __cdecl reorder(int a1)
{
  int result; // eax@1
  int v2; // esi@2
  int t; // eax@2
  int v4; // eax@4

  result = a1;
  do
  {
    v2 = 3 * result;
    t = table1[3 * result];
    if ( t != -1 )                              // -1是一个标识
      reorder(t);
    v4 = i;
    hex1[i] = cphex1[v2 * 4];                   // table3选择一个元素乘以4作为要置换的index，
                                                // 所以table3是置换表
                                                // 选择的序列是4倍的关系
    i = v4 + 1;
    result = table3[v2];
  }
  while ( result != -1 );                       // table1选择一个元素作为是否结束递归的条件
  return result;
} 
``` 

kmp生成next序列并依据next序列异或原序列
```C
int __cdecl sub_401080(int hex0, signed int len)
{
  signed int i; // esi@1
  char *p; // edi@2
  int k; // eax@3
  signed int j; // eax@10
  int *pp; // esi@11
  char v7; // dl@12
  int v9; // [sp+Ch] [bp-200h]@1
  char v10; // [sp+10h] [bp-1FCh]@2

  i = 1;
  v9 = -1;
  if ( len > 1 )
  {                                             // 和开始相等，第几个则赋值几-1
    p = &v10;
    do
    {
      for ( k = *((_DWORD *)p - 1); k != -1; k = *(&v9 + k) )// 不相等则回溯到前面相等的地方
      {
        if ( *(_BYTE *)(i + hex0) == *(_BYTE *)(hex0 + k + 1) )
          break;
      }
      if ( *(_BYTE *)(i + hex0) == *(_BYTE *)(hex0 + k + 1) )
        *(_DWORD *)p = k + 1;                   // 直到找到当前字符和next[l]相等，赋值next[l]=l+1,否则赋值-1
      else
        *(_DWORD *)p = -1;
      ++i;
      p += 4;
    }
    while ( i < len );
  }
  j = 0;
  if ( len > 0 )
  {
    pp = &v9;
    do                                          // 异或0x18加上匹配的个数
    {
      v7 = *pp + 0x19;
      ++pp;
      *(_BYTE *)(j++ + hex0) ^= v7;
    }
    while ( j < len );
  }
  return 0;
}
```
###0x01 sol.py
``` python
enc = '22722272222227272222727a2222222222272222272222222222cfdceeeebb9fdbcdbbedfdede7ce9bebe0bb1e2ceab9e2bbbdecf9d8'
table = [0x4f8, 0x258, 0x108, 0x318, 0x2b8, 0x3d8, 0x378, 0x498, 0x438, 0x60, 0x348, 0x168, 0x4c8, 0x408,
         0x138, 0x1c8, 0x198, 0x228, 0x1f8, 0x2e8, 0x288, 0x468, 0x3a8, 0xc, 0x420, 0x180, 0x4e0, 0x90,
         0x240, 0x1e0, 0x300, 0x2a0, 0x3c0, 0x360, 0x480, 0x78, 0x270, 0xc0, 0x3f0, 0x330, 0x4b0, 0xa8,
         0x450, 0xf0, 0xd8, 0x150, 0x120, 0x210, 0x1b0, 0x390, 0x2d0, 0x0, 0x48c, 0x1ec, 0x9c, 0x2ac,
         0x24c, 0x36c, 0x30c, 0x42c, 0x3cc, 0x4ec, 0x24, 0x2dc, 0xfc, 0x45c, 0x39c, 0xcc, 0x4bc, 0x15c,
         0x12c, 0x1bc, 0x18c, 0x27c, 0x21c, 0x3fc, 0x33c, 0x18, 0x3b4, 0x114, 0x474, 0x3c, 0x1d4, 0x174,
         0x294, 0x234, 0x354, 0x2f4, 0x4d4, 0x414, 0x30, 0x204, 0x54, 0x384, 0x2c4, 0x504, 0x444, 0x48,
         0x3e4, 0x84, 0x6c, 0xe4, 0xb4, 0x1a4, 0x144, 0x324, 0x264, 0x4a4]
list0 = [0 for i in range(len(table))]
i = 0
for index in table:		#zhihuan index de weizhi
	list0[index/12] = enc[i]
	i += 1
print ''.join(list1)

out1 = ''.join(list1).decode('hex')
out2 = ''
for ch in out1:
	out2 += chr(ord(ch)^0x18)
	i += 1
print out2.decode('hex')
