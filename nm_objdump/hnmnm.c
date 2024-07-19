#include "hnm.h"

/**
 * print_symbol - Prints out the relevant symbol info
 * @header: Pointer to elf_hdr struct
 * @sym64: Pointer to index in symbol table for 64 bit systems
 * @sym32: Pointer to index in symbol table for 32 bit systems
 */

void print_symbol(elf_hdr *header, Elf64_Sym *sym64, Elf32_Sym *sym32)
{
	char type;

	if (header->Flag_OP)
	{
		type = get_type64(header, sym64);
		if (type == 'a' || !header->str_table[sym64->st_name])
			return;
		if (type == 'w' || type == 'U')
			printf("%16s ", "");
		else
			printf("%016lx ", sym64->st_value);
		printf("%c ", type);
		printf("%s\n", header->str_table + sym64->st_name);
	}
	else
	{
		type = get_type32(header, sym32);
		if (type == 'a' || !header->str_table[sym32->st_name])
			return;
		if (type == 'w' || type == 'U')
			printf("%8s ", "");
		else
			printf("%08x ", sym32->st_value);
		printf("%c ", type);
		printf("%s\n", header->str_table + sym32->st_name);
	}
}

/**
 * get_type64 - gets type of symbol in one char
 * @header: Pointer to struct
 * @sym64: pointer to index in symbol table
 * Return: the char type
 */

char get_type64(elf_hdr *header, Elf64_Sym *sym64)
{
	char c;

	if (ELF64_ST_BIND(sym64->st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF64_ST_BIND(sym64->st_info) == STB_WEAK &&
		ELF64_ST_TYPE(sym64->st_info) == STT_OBJECT)
		c = sym64->st_shndx == SHN_UNDEF ? 'v' : 'V';
	else if (ELF64_ST_BIND(sym64->st_info) == STB_WEAK)
		c = sym64->st_shndx == SHN_UNDEF ? 'w' : 'W';
	else if (sym64->st_shndx == SHN_UNDEF)
		c = 'U';
	else if (sym64->st_shndx == SHN_ABS)
		c = 'A';
	else if (sym64->st_shndx == SHN_COMMON)
		c = 'C';
	else if (header->Shdr64[sym64->st_shndx].sh_type == SHT_NOBITS
			&& header->Shdr64[sym64->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'B';
	else if (header->Shdr64[sym64->st_shndx].sh_type == SHT_PROGBITS
			&& header->Shdr64[sym64->st_shndx].sh_flags == SHF_ALLOC)
		c = 'R';
	else if (header->Shdr64[sym64->st_shndx].sh_type == SHT_PROGBITS
			&& header->Shdr64[sym64->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (header->Shdr64[sym64->st_shndx].sh_type == SHT_PROGBITS
			&& header->Shdr64[sym64->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (header->Shdr64[sym64->st_shndx].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = 'T';
	if (ELF64_ST_BIND(sym64->st_info) == STB_LOCAL && c != '?')
		c += 32;
	return (c);
}

/**
 * get_type32 - Gets type of symbol in one char
 * @header: Pointer to struct
 * @sym32: Pointer to index of symbol table in 32 bit system
 * Return: Char type
 */

char get_type32(elf_hdr *header, Elf32_Sym *sym32)
{
	char  c;

	if (ELF32_ST_BIND(sym32->st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF32_ST_BIND(sym32->st_info) == STB_WEAK &&
		ELF32_ST_TYPE(sym32->st_info) == STT_OBJECT)
		c = sym32->st_shndx == SHN_UNDEF ? 'v' : 'V';
	else if (ELF32_ST_BIND(sym32->st_info) == STB_WEAK)
		c = sym32->st_shndx == SHN_UNDEF ? 'w' : 'W';
	else if (sym32->st_shndx == SHN_UNDEF)
		c = 'U';
	else if (sym32->st_shndx == SHN_ABS)
		c = 'A';
	else if (sym32->st_shndx == SHN_COMMON)
		c = 'C';
	else if (header->Shdr32[sym32->st_shndx].sh_type == SHT_NOBITS
			&& header->Shdr32[sym32->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'B';
	else if (header->Shdr32[sym32->st_shndx].sh_type == SHT_PROGBITS
			&& header->Shdr32[sym32->st_shndx].sh_flags == SHF_ALLOC)
		c = 'R';
	else if (header->Shdr32[sym32->st_shndx].sh_type == SHT_PROGBITS
			&& header->Shdr32[sym32->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (header->Shdr32[sym32->st_shndx].sh_type == SHT_PROGBITS
			&& header->Shdr32[sym32->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (header->Shdr32[sym32->st_shndx].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = 'T';
	if (ELF32_ST_BIND(sym32->st_info) == STB_LOCAL && c != '?')
		c += 32;
	return (c);
}
