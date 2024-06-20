#include "hreadelf.h"

static uint16_t bswap16(uint16_t num);
static uint32_t bswap32(uint32_t num);
static uint64_t bswap64(uint64_t num);

prog_dt prog;

int is_elf(const char *fd_map)
{
    return !memcmp(fd_map, ELFMAG, 4);
}

void error_manager(int cause, int err)
{
    if (prog.fd && prog.fd != -1)
        close(prog.fd);

    switch (cause)
	{
        case 1:
            fprintf(stderr, "%s%s'%s'%s\n", prog.name, ERR_STR, prog.file, ERR_OPEN);
            break;
        case 2:
            fprintf(stderr, "%s%s%s\n", prog.name, ERR_STR, ERR_ELF);
            break;
        default:
            break;
    }
    exit(err);
}

void convert_endian_32(Elf32_Ehdr *hdr)
{
    hdr->e_type = bswap16(hdr->e_type);
    hdr->e_machine = bswap16(hdr->e_machine);
    hdr->e_version = bswap32(hdr->e_version);
    hdr->e_entry = bswap32(hdr->e_entry);
    hdr->e_phoff = bswap32(hdr->e_phoff);
    hdr->e_shoff = bswap32(hdr->e_shoff);
    hdr->e_flags = bswap32(hdr->e_flags);
    hdr->e_ehsize = bswap16(hdr->e_ehsize);
    hdr->e_phentsize = bswap16(hdr->e_phentsize);
    hdr->e_phnum = bswap16(hdr->e_phnum);
    hdr->e_shentsize = bswap16(hdr->e_shentsize);
    hdr->e_shnum = bswap16(hdr->e_shnum);
    hdr->e_shstrndx = bswap16(hdr->e_shstrndx);
}

void convert_endian_64(Elf64_Ehdr *hdr)
{
    hdr->e_type = bswap16(hdr->e_type);
    hdr->e_machine = bswap16(hdr->e_machine);
    hdr->e_version = bswap32(hdr->e_version);
    hdr->e_entry = bswap64(hdr->e_entry);
    hdr->e_phoff = bswap64(hdr->e_phoff);
    hdr->e_shoff = bswap64(hdr->e_shoff);
    hdr->e_flags = bswap32(hdr->e_flags);
    hdr->e_ehsize = bswap16(hdr->e_ehsize);
    hdr->e_phentsize = bswap16(hdr->e_phentsize);
    hdr->e_phnum = bswap16(hdr->e_phnum);
    hdr->e_shentsize = bswap16(hdr->e_shentsize);
    hdr->e_shnum = bswap16(hdr->e_shnum);
    hdr->e_shstrndx = bswap16(hdr->e_shstrndx);
}

static uint16_t bswap16(uint16_t num)
{
    return ((num >> 8) & 0xff) | ((num << 8) & 0xff00);
}

static uint32_t bswap32(uint32_t num)
{
    return ((num >> 24) & 0xff) | ((num >> 8) & 0xff00) |
           ((num << 8) & 0xff0000) | ((num << 24) & 0xff000000);
}

static uint64_t bswap64(uint64_t num)
{
    return ((num >> 56) & 0xff) | ((num >> 40) & 0xff00) |
           ((num >> 24) & 0xff0000) | ((num >> 8) & 0xff000000) |
           ((num << 8) & 0xff00000000) | ((num << 24) & 0xff0000000000) |
           ((num << 40) & 0xff000000000000) | ((num << 56) & 0xff00000000000000);
}
