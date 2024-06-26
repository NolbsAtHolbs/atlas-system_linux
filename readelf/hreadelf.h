#ifndef HREADELF_H
#define HREADELF_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define FH_CLASS "Class:"
#define FH_DATA "Data:"
#define FH_VERSION "Version:"
#define FH_OSABI "OS/ABI:"
#define FH_ABIVERSION "ABI Version:"
#define FH_TYPE "Type:"
#define FH_MACHINE "Machine:"
#define FH_EVERSION "Version:"
#define FH_ENTRY "Entry point address:"
#define FH_PHOFF "Start of program headers:"
#define FH_SHOFF "Start of section headers:"
#define FH_FLAGS "Flags:"
#define FH_EHSIZE "Size of this header:"
#define FH_PHENTSIZ "Size of program headers:"
#define FH_PHNUM "Number of program headers:"
#define FH_SHENTSIZ "Size of section headers:"
#define FH_SHNUM "Number of section headers:"
#define FH_SHSTRNDX "Section header string table index:"
#define ERR_STR ": Error: "
#define ERR_OPEN ": No such file"
#define ERR_ELF "Not an ELF file"

/**
 * struct program_data - file reference info
 * @name: name of program
 * @file: name of input file
 * @fd: file descriptor of input file, if opened
 * @fclass: file class of input file
 * @endianness: endianness of input file
*/
typedef struct program_data
{
	char *name;
	char *file;
	int fd;
	int fclass;
	int endianness;
} prog_dt;

extern prog_dt prog;

/**
 * struct elf_data - ELF header data
 * @fh32: 32-bit ELF files
 * @fh64: 64-bit ELF files
 * @sh32: 32-bit ELF files section
 * @sh64: 64-bit ELF files section
*/
typedef struct elf_data
{
	Elf32_Ehdr fh32;
	Elf64_Ehdr fh64;
	Elf32_Shdr *sh32;
	Elf64_Shdr *sh64;
} elf_dt;

int is_elf(char *fd_map);
void error_manager(int cause, int err);
void convert_endian_32(void *data, size_t size);
void convert_endian_64(void *data, size_t size);
void fh_details_32(Elf32_Ehdr *map_32);
void fh_details_64(Elf64_Ehdr *map_64);
int sh_details_32(elf_dt *elfen);
int sh_details_64(elf_dt *elfen);

#endif
