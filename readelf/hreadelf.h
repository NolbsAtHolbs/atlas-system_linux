#ifndef HREADELF_H
#define HREADELF_H

#define FH_MAGIC "  Magic:   "
#define ERR_STR ": Error: "
#define ERR_OPEN ": File not found"
#define ERR_ELF "Not an ELF file"

#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    Elf32_Ehdr fh32;
    Elf64_Ehdr fh64;
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

void convert_endian_32(Elf32_Ehdr *hdr);
void convert_endian_64(Elf64_Ehdr *hdr);
void print_elf_details_32(const Elf32_Ehdr *hdr);
void print_elf_details_64(const Elf64_Ehdr *hdr);
int is_elf(const char *fd_map);
void error_manager(int cause, int err);

#endif
