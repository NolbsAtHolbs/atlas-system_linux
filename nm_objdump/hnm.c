#include "hnm.h"

/**
 * main - Entry to function
 * @argc: Num of args
 * @argv: Array of args
 * Return: 0 on success, else -1
 */

int main(int argc, char **argv)
{
	struct stat info;
	elf_hdr header;
	int fd;

	if (argc != 2)
	{
		fprintf(stderr, "Unsupported number of arguments\n");
		return (-1);
	}
	if (stat(argv[1], &info) == -1)
	{
		perror("stat");
		return (-1);
	}
	if (!S_ISREG(info.st_mode))
	{
		fprintf(stderr, "%s: Error: '%s' is not an ordinary file\n",
				argv[0], argv[1]);
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (map_header(&header, fd, argv[0]) == -1)
	{
		close(fd);
		return (-1);
	}
	if (header.Flag_SIG || parse_symbol_header(&header) == -1)
	{
		destroy_header(&header);
		fprintf(stderr, "%s: %s: no symbols\n", argv[0], argv[1]);
		return (0);
	}
	process_symbols(&header);
	destroy_header(&header);
	return (0);
}

/**
 * map_header - Maps open ELF file into virtual memory
 * @header: Pointer to `elf_hdr` struct
 * @fd: File descriptor for ELF file
 * @prog: Program name
 * Return: `0` on success, `-1` on failure
 */
int map_header(elf_hdr *header, int fd, char *prog)
{
	struct stat statbuf;
	void *map;

	header->fd = fd;
	if (fstat(header->fd, &statbuf) == -1)
	{
		perror("fstat");
		return (-1);
	}
	header->fsize64 = (uint64_t)statbuf.st_size;
	map = mmap(NULL, header->fsize64, PROT_READ, MAP_PRIVATE, header->fd, 0);
	if (map == MAP_FAILED)
	{
		perror("mmap");
		return (-1);
	}
	header->Ehdr64 = (Elf64_Ehdr *)map;
	if (memcmp(header->Ehdr64->e_ident, ELFMAG, SELFMAG))
	{
		fprintf(stderr, "%s: Error: Not an ELF file\n", prog);
		munmap(header->Ehdr64, header->fsize64);
		return (-1);
	}
	header->Flag_SIG = (header->Ehdr64->e_ident[EI_DATA] == ELFDATA2MSB);
	header->Flag_OP = (header->Ehdr64->e_ident[EI_CLASS] == ELFCLASS64);
	if (!header->Flag_OP)
	{
		header->fsize32 = (uint32_t)statbuf.st_size;
		header->Ehdr32 = (Elf32_Ehdr *)map;
		if (header->Ehdr32 == MAP_FAILED)
		{
			perror("mmap");
			munmap(header->Ehdr64, header->fsize64);
			return (-1);
		}
	}
	return (0);
}

/**
 * parse_symbol_header - Finds symbol-table section header and symbol count
 * @hdr: Pointer to struct
 * Return: `0` on success, `-1` on failure
 */
int parse_symbol_header(elf_hdr *hdr)
{
	uint64_t i;
	uint32_t j;

	if (hdr->Flag_OP)
	{
		hdr->Shdr64 = SECTION_HEADERS64(hdr->Ehdr64);
		hdr->Sym_sh64 = NULL;
		for (i = 0; i < SECTION_COUNT64(hdr->Ehdr64); ++i)
		{
			if (hdr->Shdr64[i].sh_type == SHT_SYMTAB)
			{
				hdr->Sym_sh64 = hdr->Shdr64 + i;
				break;
			}
		}
		if (!hdr->Sym_sh64)
			return (-1);
		hdr->Sym_count64 = SYMBOL_COUNT64(hdr->Sym_sh64);
		hdr->Sym_tbl_64 = SYMBOL_TABLE64(hdr->Ehdr64, hdr->Sym_sh64);
		hdr->str_table = STRING_TABLE(hdr->Ehdr64, hdr->Shdr64, hdr->Sym_sh64);
	}
	else
	{
		hdr->Shdr32 = SECTION_HEADERS32(hdr->Ehdr32);
		hdr->Sym_sh32 = NULL;
		for (j = 0; j < SECTION_COUNT32(hdr->Ehdr32); ++j)
		{
			if (hdr->Shdr32[j].sh_type == SHT_SYMTAB)
			{
				hdr->Sym_sh32 = hdr->Shdr32 + j;
				break;
			}
		}
		if (!hdr->Sym_sh32)
			return (-1);
		hdr->Sym_count32 = SYMBOL_COUNT32(hdr->Sym_sh32);
		hdr->Sym_tbl_32 = SYMBOL_TABLE32(hdr->Ehdr32, hdr->Sym_sh32);
		hdr->str_table = STRING_TABLE(hdr->Ehdr32, hdr->Shdr32, hdr->Sym_sh32);
	}
	return (0);
}

/**
 * destroy_header - Frees memory used by struct
 * @header: Pointer to struct
 */

void destroy_header(elf_hdr *header)
{
	if (!header)
		return;
	if (header->Flag_OP)
		munmap(header->Ehdr64, header->fsize64);
	else
		munmap(header->Ehdr32, header->fsize32);
	close(header->fd);
	memset(header, 0, sizeof(elf_hdr));
}

/**
 * process_symbols - Sequentially performs `action` on all symbols
 * @header: Pointer to `elf_hdr` structure
 */

void process_symbols(elf_hdr *header)
{
	uint64_t i;
	uint32_t j;

	if (header->Flag_OP)
	{
		for (i = 0; i < header->Sym_count64; ++i)
		{
			print_symbol(header, header->Sym_tbl_64 + i, NULL);
		}
	}
	else
	{
		for (j = 0; j < header->Sym_count32; ++j)
		{
			print_symbol(header, NULL, header->Sym_tbl_32 + j);
		}
	}
}
