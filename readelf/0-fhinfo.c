#include "hreadelf.h"

static void print_magic(const unsigned char *ident);
static void print_osabi(unsigned char osabi);
static void print_type(uint16_t type);
static void print_machine(uint16_t machine);

void print_elf_details_32(const Elf32_Ehdr *hdr)
{
    printf(FH_MAGIC);
    print_magic(hdr->e_ident);
    printf("  %-35sELF32\n", "Class:");
    printf("  %-35s%s\n", "Data:",
           hdr->e_ident[EI_DATA] == ELFDATA2LSB ?
           "2's complement, little endian" :
           "2's complement, big endian");
    printf("  %-35s%d (current)\n", "Version:", hdr->e_ident[EI_VERSION]);
    print_osabi(hdr->e_ident[EI_OSABI]);
    printf("  %-35s%d\n", "ABI Version:", hdr->e_ident[EI_ABIVERSION]);
    print_type(hdr->e_type);
    print_machine(hdr->e_machine);
    printf("  %-35s0x%x\n", "Version:", hdr->e_version);
    printf("  %-35s0x%x\n", "Entry point address:", hdr->e_entry);
    printf("  %-35s%d (bytes into file)\n", "Start of program headers:", hdr->e_phoff);
    printf("  %-35s%d (bytes into file)\n", "Start of section headers:", hdr->e_shoff);
    printf("  %-35s0x%x\n", "Flags:", hdr->e_flags);
    printf("  %-35s%d (bytes)\n", "Size of this header:", hdr->e_ehsize);
    printf("  %-35s%d (bytes)\n", "Size of program headers:", hdr->e_phentsize);
    printf("  %-35s%d\n", "Number of program headers:", hdr->e_phnum);
    printf("  %-35s%d (bytes)\n", "Size of section headers:", hdr->e_shentsize);
    printf("  %-35s%d\n", "Number of section headers:", hdr->e_shnum);
    printf("  %-35s%d\n", "Section header string table index:", hdr->e_shstrndx);
}

void print_elf_details_64(const Elf64_Ehdr *hdr)
{
    printf(FH_MAGIC);
    print_magic(hdr->e_ident);
    printf("  %-35sELF64\n", "Class:");
    printf("  %-35s%s\n", "Data:",
           hdr->e_ident[EI_DATA] == ELFDATA2LSB ?
           "2's complement, little endian" :
           "2's complement, big endian");
    printf("  %-35s%d (current)\n", "Version:", hdr->e_ident[EI_VERSION]);
    print_osabi(hdr->e_ident[EI_OSABI]);
    printf("  %-35s%d\n", "ABI Version:", hdr->e_ident[EI_ABIVERSION]);
    print_type(hdr->e_type);
    print_machine(hdr->e_machine);
    printf("  %-35s0x%x\n", "Version:", hdr->e_version);
    printf("  %-35s0x%lx\n", "Entry point address:", hdr->e_entry);
    printf("  %-35s%ld (bytes into file)\n", "Start of program headers:", hdr->e_phoff);
    printf("  %-35s%ld (bytes into file)\n", "Start of section headers:", hdr->e_shoff);
    printf("  %-35s0x%x\n", "Flags:", hdr->e_flags);
    printf("  %-35s%d (bytes)\n", "Size of this header:", hdr->e_ehsize);
    printf("  %-35s%d (bytes)\n", "Size of program headers:", hdr->e_phentsize);
    printf("  %-35s%d\n", "Number of program headers:", hdr->e_phnum);
    printf("  %-35s%d (bytes)\n", "Size of section headers:", hdr->e_shentsize);
    printf("  %-35s%d\n", "Number of section headers:", hdr->e_shnum);
    printf("  %-35s%d\n", "Section header string table index:", hdr->e_shstrndx);
}

static void print_magic(const unsigned char *ident)
{
    int i;

    for (i = 0; i < EI_NIDENT; i++)
	{
        printf("%.2x ", ident[i]);
    }
    printf("\n");
}

static void print_osabi(unsigned char osabi)
{
    printf("  %-35s", "OS/ABI:");
    switch (osabi)
	{
        case ELFOSABI_SYSV: printf("UNIX - System V\n"); break;
        case ELFOSABI_NETBSD: printf("UNIX - NetBSD\n"); break;
        case ELFOSABI_GNU: printf("UNIX - GNU\n"); break;
        case ELFOSABI_SOLARIS: printf("UNIX - Solaris\n"); break;
        case ELFOSABI_FREEBSD: printf("UNIX - FreeBSD\n"); break;
        case ELFOSABI_OPENBSD: printf("UNIX - OpenBSD\n"); break;
        case ELFOSABI_ARM: printf("UNIX - ARM\n"); break;
        default: printf("<unknown: %x>\n", osabi); break;
    }
}

static void print_type(uint16_t type)
{
    printf("  %-35s", "Type:");
    switch (type)
	{
        case ET_NONE: printf("NONE (None)\n"); break;
        case ET_REL: printf("REL (Relocatable file)\n"); break;
        case ET_EXEC: printf("EXEC (Executable file)\n"); break;
        case ET_DYN: printf("DYN (Shared object file)\n"); break;
        case ET_CORE: printf("CORE (Core file)\n"); break;
        default: printf("<unknown: %x>\n", type); break;
    }
}

static void print_machine(uint16_t machine)
{
    printf("  %-35s", "Machine:");
    switch (machine)
	{
        case EM_X86_64: printf("Advanced Micro Devices X86-64\n"); break;
        case EM_386: printf("Intel 80386\n"); break;
        case EM_SPARC: printf("Sparc\n"); break;
        default: printf("<unknown: %x>\n", machine); break;
    }
}
