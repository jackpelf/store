nt Elf32_Addr;
typedef int Elf32_Off;
typedef int Elf32_Word;
typedef short Elf32_Half;


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


