#include "hreadelf.h"

static void set_class(unsigned char clas);
static void set_endianness(unsigned char dat);
static void process_file_header(elf_dt *elfen);

prog_dt prog;

int main(int argc, char **argv)
{
    elf_dt elfen;
    memset(&elfen, 0, sizeof(elfen));

    if (argc != 2)
	{
        fprintf(stderr, "Usage: %s ELF-file\n", argv[0]);
        return 1;
    }

    prog.name = argv[0];
    prog.file = argv[1];
    prog.fd = open(argv[1], O_RDONLY);

    if (prog.fd == -1)
        error_manager(1, 1);

    if (read(prog.fd, &elfen.fh64, sizeof(elfen.fh64)) != sizeof(elfen.fh64)
		|| !is_elf((char *)&elfen.fh64))
		{
			error_manager(2, 1);
		}

    set_class(elfen.fh64.e_ident[EI_CLASS]);

    if (prog.fclass == ELFCLASS32)
	{
        lseek(prog.fd, 0, SEEK_SET);
        if (read(prog.fd, &elfen.fh32, sizeof(elfen.fh32)) != sizeof(elfen.fh32)
			|| !is_elf((char *)&elfen.fh32))
			{
				error_manager(2, 1);
			}
	}

    set_endianness(elfen.fh64.e_ident[EI_DATA]);
    process_file_header(&elfen);

    close(prog.fd);
    return 0;
}

static void set_class(unsigned char clas)
{
    prog.fclass = (clas == ELFCLASS32) ? ELFCLASS32 : ELFCLASS64;
}

static void set_endianness(unsigned char dat)
{
    prog.endianness = (dat == ELFDATA2LSB) ? 1 : 2;
}

static void process_file_header(elf_dt *elfen)
{
    printf("ELF Header:\n");

    if (prog.fclass == ELFCLASS32)
	{
        if (prog.endianness == 2)
            convert_endian_32(&elfen->fh32);
        print_elf_info_32(&elfen->fh32);
    }
	else
	{
        if (prog.endianness == 2)
            convert_endian_64(&elfen->fh64);
        print_elf_info_64(&elfen->fh64);
    }
}
