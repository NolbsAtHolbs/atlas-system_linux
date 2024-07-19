#ifndef HNM_H
#define HNM_H

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define OFFSET(ptr, n) ((char *)(ptr) + (n))
#define SECTION_HEADERS64(Ehdr64) ((Elf64_Shdr *)OFFSET((Ehdr64),\
(Ehdr64)->e_shoff))
#define SECTION_HEADERS32(Ehdr32) ((Elf32_Shdr *)OFFSET((Ehdr32),\
(Ehdr32)->e_shoff))
#define SECTION_COUNT64(Ehdr64) ((uint64_t)(Ehdr64)->e_shnum)
#define SECTION_COUNT32(Ehdr32) ((uint32_t)(Ehdr32)->e_shnum)
#define SYMBOL_COUNT64(sh) ((uint64_t)(sh)->sh_size / sizeof(Elf64_Sym))
#define SYMBOL_COUNT32(sh) ((uint32_t)(sh)->sh_size / sizeof(Elf32_Sym))
#define SECTION(ehdr, sh) OFFSET((ehdr), (sh)->sh_offset)
#define SYMBOL_TABLE64(ehdr, sh) ((Elf64_Sym *)SECTION(ehdr, sh))
#define SYMBOL_TABLE32(ehdr, sh) ((Elf32_Sym *)SECTION(ehdr, sh))
#define STRING_TABLE(ehdr, shdrs, sh) SECTION(ehdr, (shdrs) + (sh)->sh_link)
#define SYMBOL_STRING(strtab, sym) ((strtab) + (sym)->st_name)

/**
 * struct elf_hdr - Struct for 32 and 64 bit ELF file headers
 * @Ehdr32: 32 bit ELF header
 * @Ehdr64: 64 bit ELF header
 * @Shdr32: 32 bit section header
 * @Shdr64: 64 bit section header
 * @Sym_sh32: 32 bit Symbol table section header
 * @Sym_sh64: 64 bit Symbol table section header
 * @Sym_tbl_64: 64 bit Symbol Table
 * @Sym_tbl_32: 32 bit symbol Table
 * @Sym_count32: 32 bit number of symbols
 * @Sym_count64: 64 bit number of symbols
 * @str_table: Start of string table
 * @fsize32: 32 bit size of elf file
 * @fsize64: 64 bit size of elf file
 * @fd: File descriptor
 * @Flag_OP: Flag for 64 or 32 bit
 * @Flag_SIG: Flag for MSB
 */
typedef struct elf_hdr
{
	char *str_table;
	int fd;
	int Flag_OP;
	int Flag_SIG;
	Elf32_Ehdr *Ehdr32;
	Elf64_Ehdr *Ehdr64;
	Elf32_Shdr *Shdr32;
	Elf64_Shdr *Shdr64;
	Elf32_Shdr *Sym_sh32;
	Elf64_Shdr *Sym_sh64;
	Elf32_Sym *Sym_tbl_32;
	Elf64_Sym *Sym_tbl_64;
	uint32_t Sym_count32;
	uint64_t Sym_count64;
	uint64_t fsize64;
	uint32_t fsize32;
} elf_hdr;

int main(int argc, char **argv);
int map_header(elf_hdr *header, int fd, char *prog);
int parse_symbol_header(elf_hdr *header);
void destroy_header(elf_hdr *header);
void process_symbols(elf_hdr *header);
void print_symbol(elf_hdr *header, Elf64_Sym *sym64, Elf32_Sym *sym32);
char get_type64(elf_hdr *header, Elf64_Sym *sym64);
char get_type32(elf_hdr *header, Elf32_Sym *sym32);

#endif
