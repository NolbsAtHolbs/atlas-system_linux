#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

/**
 * print_elf_header - Prints the ELF header information
 * @header: Pointer to the ELF header structure
 */
void print_elf_header(Elf64_Ehdr *header)
{
	int i;
	printf("ELF Header:\n");
	printf("  Magic:   ");
	i = 0;
	while (i < EI_NIDENT)
	{
		printf("%02x ", header->e_ident[i]);
		i++;
	}
	printf("\n");
	printf("  Class:                             %s\n", 
	       header->e_ident[EI_CLASS] == ELFCLASS64 ? "ELF64" : "ELF32");
	printf("  Data:                              %s\n",
	       header->e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
	printf("  Version:                           %d (current)\n", header->e_ident[EI_VERSION]);
	printf("  OS/ABI:                            %d\n", header->e_ident[EI_OSABI]);
	printf("  ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);
	printf("  Type:                              %d\n", header->e_type);
	printf("  Machine:                           %d\n", header->e_machine);
	printf("  Version:                           0x%x\n", header->e_version);
	printf("  Entry point address:               0x%lx\n", header->e_entry);
	printf("  Start of program headers:          %ld (bytes into file)\n", header->e_phoff);
	printf("  Start of section headers:          %ld (bytes into file)\n", header->e_shoff);
	printf("  Flags:                             0x%x\n", header->e_flags);
	printf("  Size of this header:               %d (bytes)\n", header->e_ehsize);
	printf("  Size of program headers:           %d (bytes)\n", header->e_phentsize);
	printf("  Number of program headers:         %d\n", header->e_phnum);
	printf("  Size of section headers:           %d (bytes)\n", header->e_shentsize);
	printf("  Number of section headers:         %d\n", header->e_shnum);
	printf("  Section header string table index: %d\n", header->e_shstrndx);
}

/**
 * main - read file
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, else 1
 */
int main(int argc, char **argv)
{
	const char *filename;
	int fd;
	Elf64_Ehdr header;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
		return (1);
	}

	filename = argv[1];
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}

	if (read(fd, &header, sizeof(header)) != sizeof(header))
	{
		perror("read");
		close(fd);
		return (1);
	}

	if (header.e_ident[EI_MAG0] != ELFMAG0 ||
	    header.e_ident[EI_MAG1] != ELFMAG1 ||
	    header.e_ident[EI_MAG2] != ELFMAG2 ||
	    header.e_ident[EI_MAG3] != ELFMAG3)
	{
		fprintf(stderr, "Not an ELF file\n");
		close(fd);
		return (1);
	}

	print_elf_header(&header);

	close(fd);
	return (0);
}
