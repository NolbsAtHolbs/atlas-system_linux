#ifndef HREADELF_H
#define HREADELF_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define FH_MAGIC "  Magic:   "
#define ERR_STR ": Error: "
#define ERR_OPEN ": File not found"
#define ERR_ELF "Not an ELF file"

typedef struct
{
    Elf32_Ehdr fh32;
    Elf64_Ehdr fh64;
	Elf32_Shdr *sh32;
	Elf64_Shdr *sh64;
} elf_dt;

typedef struct
{
    char *name;
    char *file;
    int fd;
    int fclass;
    int endianness;
} prog_dt;

extern prog_dt prog;

void print_elf_info_32(const Elf32_Ehdr *hdr);
void print_elf_info_64(const Elf64_Ehdr *hdr);
void print_section_headers_32(const Elf32_Shdr *shdr, const char *shstr, int num);
void print_section_headers_64(const Elf64_Shdr *shdr, const char *shstr, int num);
void convert_endian_32(Elf32_Ehdr *hdr);
void convert_endian_64(Elf64_Ehdr *hdr);
int is_elf(const char *fd_map);
void error_manager(int cause, int err);

#endif
