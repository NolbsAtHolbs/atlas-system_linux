#include "hreadelf.h"

static const char *get_section_type(uint32_t sh_type);
static const char *get_section_flags(uint64_t sh_flags);
static void print_section_flags_key(void);

/**
 * print_section_headers_32 - prints section headers for 32-bit ELF file
 * @shdr: section header array for 32-bit ELF file
 * @shstr: section header string table
 * @num: number of section headers
 */
void print_section_headers_32(const Elf32_Shdr *shdr, const char *shstr, int num)
{
	int i;

	printf("There are %d section headers, starting at offset 0x%x:\n\n",
	       num, shdr->sh_offset);

	printf("Section Headers:\n");
	printf("  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n");

	for (i = 0; i < num; i++)
	{
		printf("  [%2d] %-17s %-15s %08x %06x %06x %02x %3s %2d %3d %2d\n",
		       i, shstr + shdr[i].sh_name, get_section_type(shdr[i].sh_type),
		       shdr[i].sh_addr, shdr[i].sh_offset, shdr[i].sh_size,
		       shdr[i].sh_entsize, get_section_flags(shdr[i].sh_flags),
		       shdr[i].sh_link, shdr[i].sh_info, shdr[i].sh_addralign);
	}
	print_section_flags_key();
}

/**
 * print_section_headers_64 - prints section headers for 64-bit ELF file
 * @shdr: section header array for 64-bit ELF file
 * @shstr: section header string table
 * @num: number of section headers
 */
void print_section_headers_64(const Elf64_Shdr *shdr, const char *shstr, int num)
{
	int i;

	printf("There are %d section headers, starting at offset 0x%lx:\n\n",
	       num, shdr->sh_offset);

	printf("Section Headers:\n");
	printf("  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al\n");

	for (i = 0; i < num; i++)
	{
		printf("  [%2d] %-17s %-15s %016lx %06lx %06lx %02lx %3s %2d %3u %2lu\n",
		       i, shstr + shdr[i].sh_name, get_section_type(shdr[i].sh_type),
		       shdr[i].sh_addr, shdr[i].sh_offset, shdr[i].sh_size,
		       shdr[i].sh_entsize, get_section_flags(shdr[i].sh_flags),
		       shdr[i].sh_link, shdr[i].sh_info, shdr[i].sh_addralign);
	}
	print_section_flags_key();
}

/**
 * get_section_type - returns a string representation of the section type
 * @sh_type: section type value
 * Return: string representation of the section type
 */
static const char *get_section_type(uint32_t sh_type)
{
	switch (sh_type)
	{
	case SHT_NULL:       return "NULL";
	case SHT_PROGBITS:   return "PROGBITS";
	case SHT_SYMTAB:     return "SYMTAB";
	case SHT_STRTAB:     return "STRTAB";
	case SHT_RELA:       return "RELA";
	case SHT_HASH:       return "HASH";
	case SHT_DYNAMIC:    return "DYNAMIC";
	case SHT_NOTE:       return "NOTE";
	case SHT_NOBITS:     return "NOBITS";
	case SHT_REL:        return "REL";
	case SHT_SHLIB:      return "SHLIB";
	case SHT_DYNSYM:     return "DYNSYM";
	case SHT_INIT_ARRAY: return "INIT_ARRAY";
	case SHT_FINI_ARRAY: return "FINI_ARRAY";
	case SHT_PREINIT_ARRAY: return "PREINIT_ARRAY";
	case SHT_GROUP:      return "GROUP";
	case SHT_SYMTAB_SHNDX: return "SYMTAB_SHNDX";
	default:             return "UNKNOWN";
	}
}

/**
 * get_section_flags - returns a string representation of the section flags
 * @sh_flags: section flags value
 * Return: string representation of the section flags
 */
static const char *get_section_flags(uint64_t sh_flags)
{
	static char flags[10];
	int pos = 0;

	if (sh_flags & SHF_WRITE)      flags[pos++] = 'W';
	if (sh_flags & SHF_ALLOC)      flags[pos++] = 'A';
	if (sh_flags & SHF_EXECINSTR)  flags[pos++] = 'X';
	if (sh_flags & SHF_MERGE)      flags[pos++] = 'M';
	if (sh_flags & SHF_STRINGS)    flags[pos++] = 'S';
	if (sh_flags & SHF_INFO_LINK)  flags[pos++] = 'I';
	if (sh_flags & SHF_LINK_ORDER) flags[pos++] = 'L';
	if (sh_flags & SHF_GROUP)      flags[pos++] = 'G';
	if (sh_flags & SHF_TLS)        flags[pos++] = 'T';
	if (sh_flags & SHF_EXCLUDE)    flags[pos++] = 'E';
	if (sh_flags & SHF_OS_NONCONFORMING) flags[pos++] = 'O';
	if (sh_flags & SHF_MASKOS)     flags[pos++] = 'o';
	if (sh_flags & SHF_MASKPROC)   flags[pos++] = 'p';
	flags[pos] = '\0';

	return flags;
}

/**
 * print_section_flags_key - prints the key to section flags
 */
static void print_section_flags_key(void)
{
	printf("Key to Flags:\n");
	printf("  W (write), A (alloc), X (execute), M (merge), S (strings)\n");
	printf("  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)\n");
	printf("  O (extra OS processing required), o (OS specific), p (processor specific)\n");
}
