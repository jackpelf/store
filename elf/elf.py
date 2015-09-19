from binascii import *
from struct import *

def tran_small(h):
	res = ''
	for i in range(len(h)/2):
		res += h[len(h) - (i + 1)*2:len(h) +2 - (i + 1)*2]
	return res

def p(h):
	return tran_small( b2a_hex(h) )


d_class = {	'00':"invalid", 
		'01':"32",
		 '02':'64'}

d_data = {	'00':'invalid',
		'01':'little', 
		'02':'big'}

d_type = {	'0000':"unknown", 
		"0001":"ET_REL", 
		"0002":"ET_EXEC", 
		"0003":"ET_DYN", 
		"0004":"ET_CORE", 	
		"ff00":"ET_LOPROC", 
		"ffff":"ET_HIPROC"}

d_machine = {	"0000":"unkown", 
		"0001":"EM_M32",
		"0002":"EM_SPARC",
		"0003":"EM_386",
                "0004":"EM_68k",
		"0005":"EM_88k",
                "0006":"EM_???",
		"0007":"EM_860",
       		"0008":"EM_MIPS"}

d_version = {	"00000000":"EV_NONE",
		"00000001":"EV_CURRENT"}


d_sh_type = {	"00000000":"NULL",
		"00000001":"PROGBITS",
		"00000002":"SYMTAB",
		"00000003":"STRTAB",
		"00000004":"RELA",
		"00000005":"HASH",
		"00000006":"DYNAMIC",
		"00000007":"NOTE",
		"00000008":"NOBITS",
		"00000009":"REL",
		"0000000a":"SHLIB",
		"0000000b":"DYNSYM",
		"70000000":"LOPROC",
		"7fffffff":"HIPROC",
		"80000000":"LOUSER",
		"8fffffff":"HIUSER",
		"6ffffff6":"GUNHASH",
		"6fffffff":"VERSYM",
		"6ffffffe":"VERNEED",
		"0000000e":"INIT_ARRY",
		"0000000f":"FINT_ARRY"}


d_sh_flags = {	"00000000":" ",
		"00000001":"W",
		"00000002":"A",
		"00000004":"X",
		"00000007":"AWX",
		"00000003":"AW",
		"00000006":"AX",
		"00000005":"WX",
		"00000030":"MS",
		"00000042":"AI"}

d_st_bind = {	"00":"LOCAL",
		"01":"GLOBAL",
		"02":"WEAK",
		"0d":"LOPROC",
		"0f":"HIPROC"}

d_st_type = {	"0":"NOTYPE",
		"1":"OBJECT",
		"2":"FUNC",
		"3":"SECTION",
		"4":"FILE",
		"d":"LOPROC",
		"f":"HIPROC"}

class e_ident():
	ei_magic = 'dskjl'
	ei_class = ''
	ei_data = ''
	ei_version = ''
	ei_pad = ''
	ei_nident = ''

class elf_header(e_ident):
	e_type = "" 
	e_machine = ''
	e_version = ''
	e_entry = ''
	e_phoff = ''
	e_shoff = ''
	e_flags = ''
	e_ehsize = ''
	e_phentsize = ''
	e_phnum = ''
	e_shentsize = ''
	e_shnum = ''
	e_shstrndx = ''
	def __init__(self):
		pass


class section_header():
	sh_name = ''
	sh_type = ''
	sh_flags = ''
	sh_addr = ''
	sh_offset = ''
	sh_size = ''
	sh_link = ''
	sh_info = ''
	sh_addralign = ''
	sh_entsize = ''

	def __init__(self):
		pass
class sym_section():
	st_name = ''
	st_value = ''
	st_size = ''
	st_info = ''
	st_other = ''
	st_shndx = ''
	
	def __init__(self):
		pass


class elf(elf_header):
	def __init__(self):
		self.fp = open("a.out")
		self.sections = []
		self.sym_sections = []

		self.read_header()
		self.print_header()
		self.read_sections()
		self.print_sections()
		self.read_sym_sections()
		self.print_sym_sections()



	def read_header(self):
		elf_header.ei_magic 	= p( self.fp.read(4) )
		elf_header.ei_class 	= d_class[ p( self.fp.read(1) ) ]
		elf_header.ei_data  	= d_data[ p( self.fp.read(1) ) ]
		elf_header.ei_version 	= p( self.fp.read(1) )
		elf_header.ei_pad 	= p( self.fp.read(8) )
		elf_header.ei_nident 	= p( self.fp.read(1) )
		self.e_type			= d_type[ p( self.fp.read(2) ) ]
		self.e_machine		= d_machine[ p( self.fp.read(2) ) ] 
		self.e_version		= d_version[ p( self.fp.read(4) ) ]
		self.e_entry			= p( self.fp.read(4) ) 
		self.e_phoff			= p( self.fp.read(4) )
		self.e_shoff			= p( self.fp.read(4) ) 
		self.e_flags			= p( self.fp.read(4) ) 
		self.e_ehsize		= p( self.fp.read(2) ) 
		self.e_phentsize		= p( self.fp.read(2) ) 
		self.e_phnum 		= p( self.fp.read(2) ) 
		self.e_shentsize 		= p( self.fp.read(2) ) 
		self.e_shnum 		= p( self.fp.read(2) ) 
		self.e_shstrndx		= p( self.fp.read(2) ) 

	def print_header(self):
		print "magic:		%10s" %elf_header.ei_magic 			
                print "class:		%10s" %elf_header.ei_class
		print "data:		%10s" %elf_header.ei_data
		print "type:		%10s" %self.e_type			
		print "machine:		%10s" %self.e_machine		
		print "version:		%10s" %self.e_version		
		print "entry:		%10s" %self.e_entry			
		print "phoff:		%10s" %self.e_phoff			
		print "shoff:		%10s" %self.e_shoff			
		print "flags:		%10s" %self.e_flags			
		print "ehsize:		%10s" %self.e_ehsize		
		print "phentsize:      %10s" %self.e_phentsize		
		print "phnum:		%10s" %self.e_phnum 		
		print "shentsize:      %10s" %self.e_shentsize 		
		print "shnum:		%10s" %self.e_shnum 		
		print "shstrndx:	%10s" %self.e_shstrndx		

	def read_sections(self):
		self.fp.seek( unpack(">l",a2b_hex(self.e_shoff))[0], 0)
		for i in range(unpack(">h",a2b_hex(self.e_shnum))[0]):
			tmp = section_header()
			tmp.sh_name 		= p( self.fp.read(4) )	
			tmp.sh_type		= d_sh_type[ p( self.fp.read(4) ) ]
			tmp.sh_flags		= d_sh_flags[ p( self.fp.read(4) ) ]
			tmp.sh_addr		= p( self.fp.read(4) )	
			tmp.sh_offset		= p( self.fp.read(4) )	
			tmp.sh_size		= p( self.fp.read(4) )	
			tmp.sh_link		= p( self.fp.read(4) )	
			tmp.sh_info		= p( self.fp.read(4) )	
			tmp.sh_addralign	= p( self.fp.read(4) )	
			tmp.sh_entsize		= p( self.fp.read(4) )	
			self.sections.append(tmp)


	def print_sections(self):
		print "%10s%10s%10s%10s%10s%10s%10s%10s%10s%10s"\
		%("name",\
		"type",\
		"flags",\
		"addr",\
		"offset",\
		"size",\
		"link",\
		"info",\
		"addralign",\
		"entsize")
			
		for i in range(unpack(">h",a2b_hex(self.e_shnum))[0]):
			print "%10s%10s%10s%10s%10s%10s%10s%10s%10s%10s" \
			%(self.sections[i].sh_name \
			,self.sections[i].sh_type \
			,self.sections[i].sh_flags \
			,self.sections[i].sh_addr \
			,self.sections[i].sh_offset[-7:] \
			,self.sections[i].sh_size[-7:] \
			,self.sections[i].sh_link \
			,self.sections[i].sh_info \
			,self.sections[i].sh_addralign \
			,self.sections[i].sh_entsize )


	def read_sym_sections(self):
		for item in self.sections[::-1]:
			if item.sh_type == "SYMTAB":
				tmp = item
				break
		symoff = unpack(">l", a2b_hex(tmp.sh_offset))[0]
		size = unpack(">l", a2b_hex(tmp.sh_size))[0]
		self.fp.seek(symoff, 0)
		for i in range(size / 16):
			tmp = sym_section()
			tmp.st_name 	= p( self.fp.read(4) )
			tmp.st_value	= p( self.fp.read(4) )
			tmp.st_size	= p( self.fp.read(4) )
			tmp.st_info	= p( self.fp.read(1) ) 
			tmp.st_other	= p( self.fp.read(1) )
			tmp.st_shndx	= p( self.fp.read(2) )
			self.sym_sections.append(tmp)
	def print_sym_sections(self):
		for item in self.sections[::-1]:
			if item.sh_type == "SYMTAB":
				tmp = item
				break
		symoff = unpack(">l", a2b_hex(tmp.sh_offset))[0]
		size = unpack(">l", a2b_hex(tmp.sh_size))[0]
		print "%5s%10s%10s%10s%10s%10s%10s%10s" %("num","name", "value", "size", "type","bind", "other", "shndx")	
		for i in range(size / 16):
			print "%5d%10s%10s%10s%10s%10s%10s%10s" \
			%(i\
			,self.sym_sections[i].st_name\
			,self.sym_sections[i].st_value\
			,self.sym_sections[i].st_size[0]\
			,d_st_type[ self.sym_sections[i].st_info[0] ]\
			, self.sym_sections[i].st_info[1] \
			,self.sym_sections[i].st_other\
			,self.sym_sections[i].st_shndx)
		




if __name__ == '__main__':
	test = elf()
