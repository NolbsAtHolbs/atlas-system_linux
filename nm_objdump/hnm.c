#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <libelf.h>
#include <gelf.h>

void print_symbols(const char *filename)
{
    int fd;
    Elf *e;
    size_t n;
    GElf_Shdr shdr;
    Elf_Scn *scn = NULL;
    Elf_Data *data = NULL;

    if (elf_version(EV_CURRENT) == EV_NONE)
    {
        fprintf(stderr, "ELF library initialization failed: %s\n", elf_errmsg(-1));
        exit(EXIT_FAILURE);
    }

    if ((fd = open(filename, O_RDONLY, 0)) < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if ((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
    {
        fprintf(stderr, "elf_begin() failed: %s.\n", elf_errmsg(-1));
        exit(EXIT_FAILURE);
    }

    if (elf_kind(e) != ELF_K_ELF)
    {
        fprintf(stderr, "%s is not an ELF object.\n", filename);
        exit(EXIT_FAILURE);
    }

    while ((scn = elf_nextscn(e, scn)) != NULL)
    {
        gelf_getshdr(scn, &shdr);

        if (shdr.sh_type == SHT_SYMTAB || shdr.sh_type == SHT_DYNSYM)
        {
            if ((data = elf_getdata(scn, NULL)) == NULL)
                continue;

            for (n = 0; n < shdr.sh_size / shdr.sh_entsize; n++)
            {
                GElf_Sym sym;
                gelf_getsym(data, n, &sym);

                char *name = elf_strptr(e, shdr.sh_link, sym.st_name);
                char type = '?';

                switch (GELF_ST_TYPE(sym.st_info))
                {
                case STT_NOTYPE:
                    type = 'n';
                    break;
                case STT_OBJECT:
                    type = 'd';
                    break;
                case STT_FUNC:
                    type = 't';
                    break;
                case STT_SECTION:
                    type = 's';
                    break;
                case STT_FILE:
                    type = 'f';
                    break;
                }

                printf("%016lx %c %s\n", (unsigned long)sym.st_value, type, name);
            }
        }
    }

    elf_end(e);
    close(fd);
}

int main(int argc, char **argv)
{
	int i;
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s [objfile ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (i = 1; i < argc; i++)
    {
        print_symbols(argv[i]);
    }

    return (0);
}
