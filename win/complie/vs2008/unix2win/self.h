
typedef unsigned int Elf32_Addr;
typedef unsigned short Elf32_Half;
typedef unsigned int Elf32_Off;
typedef int Elf32_Sword;
typedef unsigned int Elf32_Word;


typedef struct{
	unsigned char e_ident[16];
	Elf32_Half e_type;
	Elf32_Half e_machine;
	Elf32_Word e_version;
	Elf32_Addr e_entry;
	Elf32_Off e_phoff;
	Elf32_Off e_shoff;
	Elf32_Word e_flags;
	Elf32_Half e_ehsize;
	Elf32_Half e_phentsize;
	Elf32_Half e_phnum;
	Elf32_Half e_shentsize;
	Elf32_Half e_shnum;
	Elf32_Half e_shstrndx;
}Elf32_Ehdr;

typedef struct elf32_phdr{  
	Elf32_Word    p_type;   
	Elf32_Off      p_offset;  
	Elf32_Addr    p_vaddr;        /* virtual address */  
	Elf32_Addr    p_paddr;        /* ignore */  
	Elf32_Word    p_filesz;       /* segment size in file */  
	Elf32_Word    p_memsz;        /* size in memory */  
	Elf32_Word    p_flags;  
	Elf32_Word    p_align;       
} Elf32_Phdr; 

typedef struct{
	Elf32_Word sh_name;
	Elf32_Word sh_type;
	Elf32_Word sh_flags;
	Elf32_Addr sh_addr;
	Elf32_Off sh_offset;
	Elf32_Word sh_size;
	Elf32_Word sh_link;
	Elf32_Word sh_info;
	Elf32_Word sh_addralign;
	Elf32_Word sh_entsize;
}Elf32_Shdr;

typedef struct{ 
	Elf32_Sword d_tag; 
	union { 
		Elf32_Sword d_val;
		Elf32_Addr d_ptr;
	} d_un; 
}Elf32_Dyn; 

typedef struct {
	Elf32_Word st_name;
	Elf32_Addr st_value;
	Elf32_Word st_size;
	unsigned char st_info;
	unsigned char st_other;
	Elf32_Half st_shndx;
 } Elf32_sym; 

typedef struct {
	Elf32_Addr r_offset;
	Elf32_Word r_info;
} Elf32_Rel;


typedef struct{
	char name[20];
	LPVOID *pf;
}fitem;
typedef struct{
	int max;
	fitem fitems[40];
}fchart;


typedef struct{
	int max;
	HMODULE hms[20];
}hmlist;




LPVOID alloc_u_r(int addr, int size)
{
	int i,j,n;
//reserve
	LPBYTE p;
//	puts("alloc reserve!");
	if(p = (LPBYTE) VirtualAlloc((LPVOID *)(addr), size, MEM_TOP_DOWN|MEM_RESERVE, PAGE_READWRITE))
	{
		;
//		puts("reserve alloc success");
	}
	else
		;
		//printf("error: %d\n",GetLastError());
	//printf("Addr: %p\n", p);
	return p;
}

LPVOID alloc_u_c(int addr, int size)
{
//commit
	LPBYTE pp;
	//puts("alloc commit!");
	if(pp = (LPBYTE) VirtualAlloc((LPVOID*)addr, size, MEM_COMMIT, PAGE_READWRITE))
	{
		;
		//puts("commit alloc success");
	}
	else 
		;
		//printf("error: %d\n",GetLastError());
	//printf("Addr: %p\n", pp);
	return pp;

}



void leak(char *p, int size)
{
	int h;
	char *ppp = p;
	for(h=0;h<size;h++)
	{
		if(h%16 == 0)
			printf("\n%6p ",ppp);
		printf("%02x ",(unsigned char)*ppp&0xff);
		ppp++;
	}
	putchar('\n');
}
bool write_mem(int addr, int filesz, int size, char *buf)
{
	char *p = (char*)addr;
	alloc_u_c(addr, size);
	int i;
	for(i=0; i<filesz; i++)
		*(p+i) = buf[i];
	for(; i<filesz; i++)
		*(p+i) = 0;
	return true;
}



