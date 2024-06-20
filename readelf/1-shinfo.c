#include "hreadelf.h"

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
	printf("  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al\n");

	for (i = 0; i < num; i++)
	{
		printf("  [%2d] %-17s %-15s %08x %06x %06x %02x %3s %2d %3d %2d\n",
			i, shstr + shdr[i].sh_name, "Section Type",
			shdr[i].sh_addr, shdr[i].sh_offset, shdr[i].sh_size,
			shdr[i].sh_entsize, "Flg", shdr[i].sh_link,
			shdr[i].sh_info, shdr[i].sh_addralign);
	}
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
			i, shstr + shdr[i].sh_name, "Section Type",
			shdr[i].sh_addr, shdr[i].sh_offset, shdr[i].sh_size,
			shdr[i].sh_entsize, "Flg", shdr[i].sh_link,
			shdr[i].sh_info, shdr[i].sh_addralign);
	}
}
