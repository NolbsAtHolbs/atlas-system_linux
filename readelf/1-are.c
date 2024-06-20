#include "hreadelf.h"

static void set_class(unsigned char clas);
static void set_endianness(unsigned char dat);
static void process_section_headers(elf_dt *elfen, char *map);

prog_dt prog;

/**
 * main - entry to program
 * @argc: count of arguments to program upon launch
 * @argv: vector of arguments to program upon launch
 * Return: 0 upon success
 */
int main(int argc, char **argv)
{
    elf_dt elfen;
    struct stat st;
    char *map;

    memset(&elfen, 0, sizeof(elfen));

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s ELF-file\n", argv[0]);
        return (1);
    }

    prog.name = argv[0];
    prog.file = argv[1];
    prog.fd = open(argv[1], O_RDONLY);

    if (prog.fd == -1)
    {
        error_manager(1, 1);
    }

    if (fstat(prog.fd, &st) != 0)
    {
        error_manager(1, 1);
    }

    map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, prog.fd, 0);

    if (map == MAP_FAILED)
    {
        error_manager(1, 1);
    }

    if (!is_elf(map))
    {
        error_manager(2, 1);
    }

    memcpy(&elfen.fh64, map, sizeof(elfen.fh64));

    set_class(elfen.fh64.e_ident[EI_CLASS]);

    if (prog.fclass == ELFCLASS32)
    {
        memcpy(&elfen.fh32, map, sizeof(elfen.fh32));
    }

    set_endianness(elfen.fh64.e_ident[EI_DATA]);
    process_section_headers(&elfen, map);

    close(prog.fd);
    munmap(map, st.st_size);
    return (0);
}

/**
 * set_class - sets fclass value in program data struct
 * @clas: unsigned char representing file class of ELF file
 */
static void set_class(unsigned char clas)
{
    if (clas == ELFCLASS32)
    {
        prog.fclass = ELFCLASS32;
    }
    else if (clas == ELFCLASS64)
    {
        prog.fclass = ELFCLASS64;
    }
}

/**
 * set_endianness - sets endianness value in program data struct
 * @dat: unsigned char representing endianness of ELF file
 */
static void set_endianness(unsigned char dat)
{
    if (dat == ELFDATA2LSB)
    {
        prog.endianness = 1;
    }
    else if (dat == ELFDATA2MSB)
    {
        prog.endianness = 2;
    }
}

/**
 * process_section_headers - manages print of section header information from input file
 * @elfen: ELF file data struct
 * @map: pointer to memory-mapped ELF file
 */
static void process_section_headers(elf_dt *elfen, char *map)
{
    if (prog.fclass == ELFCLASS32)
    {
        elfen->sh32 = (Elf32_Shdr *)(map + elfen->fh32.e_shoff);
        if (elfen->fh32.e_shstrndx < elfen->fh32.e_shnum)
        {
            print_section_headers_32(elfen->sh32, map + elfen->sh32[elfen->fh32.e_shstrndx].sh_offset, elfen->fh32.e_shnum);
        }
        else
        {
            fprintf(stderr, "Invalid section header string table index\n");
            error_manager(2, 1);
        }
    }
    else if (prog.fclass == ELFCLASS64)
    {
        elfen->sh64 = (Elf64_Shdr *)(map + elfen->fh64.e_shoff);
        if (elfen->fh64.e_shstrndx < elfen->fh64.e_shnum)
        {
            print_section_headers_64(elfen->sh64, map + elfen->sh64[elfen->fh64.e_shstrndx].sh_offset, elfen->fh64.e_shnum);
        }
        else
        {
            fprintf(stderr, "Invalid section header string table index\n");
            error_manager(2, 1);
        }
    }
}
