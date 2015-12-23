#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include "self.h"
#include "func.h"

void dl_resolv_init();
void dl_resolv(int );
void load();

Elf32_Ehdr e_h;

Elf32_Addr dym_addr;
Elf32_Addr got_addr;
Elf32_Addr rel_addr;
Elf32_Addr sym_addr;
Elf32_Addr str_addr;

char buf[0xffffff];
FILE *fp;

int main(int argc, char** argv)
{
	puts("VERSION 0.65!");
//	HMODULE kkk = LoadLibrary("msvcrt.dll");
//	printf("%p\n", GetProcAddress(kkk, "puts"));
	if(argc == 1)
	{
		puts("<usage>: filename");
		exit(0);
	}
	getchar();

	fp = fopen(argv[1], "rb");
	dl_resolv_init();
	//puts("test getaddrsss");
	//printf("0x%p\n\n\n\n", GetProcAddress(m_list.hms[0], "printf"));

	load();

//	dl_resolv(0x8);


	puts("\n\nRun End !");
  	fclose(fp);
	return 0;
}

void dl_resolv_init()
{
	Elf32_Shdr e_s;
	Elf32_Dyn e_d;
	int d_offset;
	int i;

	init_chart();

		
	fseek(fp, 0, 0);
	fread(&e_h, 0x34u, 1u, fp);
	//printf("entry: %p\n",e_h.e_entry);
	for ( i = 0; i < e_h.e_shnum; ++i )
	{
		fseek(fp, e_h.e_shoff+ 40 * i, 0);
		fread(&e_s, 0x28u, 1u, fp);
		if ( e_s.sh_type == 6 )		//dynamic
		{
			dym_addr = e_s.sh_addr;
			d_offset = e_s.sh_offset;
			//puts("ssssssssssssss");
			//printf("common: %p\n",e_s.sh_addr);
		}
	}
	for ( i = 0; ; ++i )
	{
		fseek(fp, d_offset+ 8 * i, 0);
		fread(&e_d, 8u, 1u, fp);
		if ( e_d.d_tag == 23 )		//rel
			rel_addr = e_d.d_un.d_ptr;
		if ( e_d.d_tag  == 3 )		//gotplt
			got_addr = e_d.d_un.d_ptr;
		if ( e_d.d_tag  == 6 )		//sym
			sym_addr = e_d.d_un.d_ptr;
		if ( e_d.d_tag  == 5 )		//str
			str_addr = e_d.d_un.d_ptr;
		if ( !e_d.d_tag  )
			break;
	}
//	printf("common: %p\n",rel_addr);
//	printf("common: %p\n",got_addr);
//	printf("common: %p\n",sym_addr);
//	printf("common: %p\n",str_addr);

}                               
void dl_resolv(int off)
{                    
	int i_sym,i;
	Elf32_Addr got_tmp;
	Elf32_Addr pf_tmp;
	char *name;
	
	//find index
	i_sym = (*(Elf32_Rel*)(off + rel_addr)).r_info >> 8; 
	got_tmp = (*(Elf32_Rel*)(off + rel_addr)).r_offset;
	name = (char*)((*(Elf32_sym*)(sym_addr + 16 * i_sym)).st_name + str_addr);

	// self_searching
	bool found = false;
	for ( i = 0; i < chart.max; ++i )
	{
		if ( !strcmp(name, chart.fitems[i].name) )
		{
			pf_tmp = (Elf32_Addr)chart.fitems[i].pf;
			found = true;
			break;
		}
	}                                             // 

	//dll searching
	if (found == false)
	{
		int sig;
		//puts(name);
		//puts("dll searching");
		pf_tmp = (Elf32_Addr)find_f(name);
		if (!pf_tmp) 
			printf("%s not found \n", name);
	}

	//change got
	*(Elf32_Addr*)got_tmp = pf_tmp;

	//esp
	__asm{
		mov ebx, ebx;
		mov ebx, ebx;
		mov ebx, ebx;
		mov ebx, ebx;
		mov eax, pf_tmp;
		lea esp, [ebp+0Ch];
		mov ebp, [ebp];		//改为原函数的ebp
		jmp eax;
	}


                                
}                               
void load()                     
{
	int i;
	Elf32_Phdr e_p;
	unsigned int max = 0,min = 0xffffffff;
	
	for ( i = 0; i < e_h.e_phnum; ++i )
	{
		fseek(fp, e_h.e_phoff + 32 * i, 0);
		fread(&e_p, 0x20u, 1u, fp);
		if ( e_p.p_type== 1 )
		{
			if ( max < e_p.p_vaddr + e_p.p_memsz)
				max = e_p.p_vaddr + e_p.p_memsz;
			if ( min > e_p.p_vaddr)
				min = e_p.p_vaddr ;
		}
	}
	//printf("%p    %p\n",max,min);
	alloc_u_r(min, max-min);

	for ( i = 0; i < e_h.e_phnum; ++i )
	{
		fseek(fp, e_h.e_phoff + 32 * i, 0);
		fread(&e_p, 0x20u, 1u, fp);
		if ( e_p.p_type == 1 )
		{
			fseek(fp, e_p.p_offset, 0);
			fread(&buf, 1u, e_p.p_filesz, fp);
			write_mem(e_p.p_vaddr, e_p.p_filesz, e_p.p_memsz, buf);
		}
	}
	//puts("sigsigsigsigsigsigsigsigsig");
	*(Elf32_Addr*)(got_addr + 8) = (Elf32_Addr)dl_resolv;
	Elf32_Addr main_addr;
	main_addr = (*(Elf32_Addr*)(e_h.e_entry + 24));
	((int (*)())main_addr)();
}


