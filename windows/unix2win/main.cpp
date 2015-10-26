#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include "WinBase.h"
#include "self.h"

LPVOID alloc_u(int flag, int addr, int size)
{
	int i,j,n;
	puts("\n\nhello world!");
	if(flag)
	{
//first
	LPBYTE p = (LPBYTE) VirtualAlloc((LPVOID *)(addr), size, MEM_TOP_DOWN|MEM_RESERVE, PAGE_READWRITE);
	printf("error: %d\n",GetLastError());
	printf("Addr: %p\n", p);
	}
//second
	LPBYTE pp = (LPBYTE) VirtualAlloc((LPVOID*)addr, size, MEM_COMMIT, PAGE_READWRITE);
	printf("error: %d\n",GetLastError());
	printf("Addr: %p\n\n", pp);
	return pp;

/*
//readwrite
	char *q = (char*)p;
	printf("q: %p\n", p);
	puts("reading");
	for(i=0 ;i< 0x20; i++)
		printf("%d\n", *(q+i));
	puts("done");
	puts("writing");
	for(i=0 ;i< 0x20; i++)
		*(q+i) = i;
	puts("done");
	puts("reading");
	for(i=0 ;i< 0x20; i++)
		printf("%d\n", *(q+i));
	puts("done");
	puts("bye");
	Sleep(1000);
*/
}

void func()
{
	FILE *fp;
	int i;
	Elf32_Ehdr testh;
	Elf32_Phdr testp;

	puts("\n\nVERSION 22!");
	fp = fopen("pwnme", "rb");
	char buf[1000];
	fread(&testh, sizeof(Elf32_Ehdr), 1, fp);
	printf("entry : %p\n", testh.e_entry);
	printf("phoff: %p\n", testh.e_phoff);
	printf("pnum: %p\n", testh.e_phnum);

	for(i=0; i<testh.e_phnum; i++)
	{
		fseek(fp, testh.e_phoff + i*sizeof(Elf32_Phdr), 0);
		fread(&testp, sizeof(Elf32_Phdr), 1, fp);
		if(testp.p_type==1)
		{
	//		alloc_u(testp.p_vaddr,

			printf("\n\ntype: %p\n", testp.p_type);
			printf("vaddr: %p\n", testp.p_vaddr);
			printf("paddr: %p\n", testp.p_paddr);
			printf("filesz: %p\n", testp.p_filesz);
			printf("memsz: %p\n", testp.p_memsz);
			printf("p_align: %p\n\n", testp.p_align);
		}
	}
	


	fclose(fp);
}


int main(int argc, char* argv[])
{
	LPVOID p;
	puts("VERSION 29!");
	p = alloc_u(1, 0x8049f08, 0x1000);

	p = alloc_u(0, 0x8047399, 0x1000);
	printf("alloc_u addr : %p\n", p);

	p = alloc_u(0, 0x8040f08, 0x1000);
	printf("alloc_u addr : %p\n", p);
	//func();
}

