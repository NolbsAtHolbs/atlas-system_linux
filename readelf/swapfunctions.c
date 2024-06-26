#include "hreadelf.h"

/**
 * is_elf - checks if ELF file
 * @fd_map: mmap of input file
 * Return: 1 if magic number found (ELF), 0 otherwise (not ELF)
*/
int is_elf(char *fd_map)
{
	return (!memcmp(fd_map, ELFMAG, 4));
}

/**
 * error_manager - prints error and/or closes fd
 * @cause: case handling
 * @err: used for exit status
*/
void error_manager(int cause, int err)
{
	if (prog.fd && prog.fd != -1)
		close(prog.fd);
	switch (cause)
	{
		case 0:
			break;
		case 1:
			fprintf(stderr, "%s%s'%s'%s\n",
				prog.name, ERR_STR, prog.file, ERR_OPEN);
			break;
		case 2:
			fprintf(stderr, "%s%s%s\n", prog.name, ERR_STR, ERR_ELF);
			break;
		default:
			break;
	}
	exit(err);
}

/**
 * convert_endian_32 - converts 32-bit ELF data
 * @data: pointer to the data
 * @size: size of the data
*/
void convert_endian_32(void *data, size_t size)
{
	uint32_t *num = data;
	size_t i;

	for (i = 0; i < size / sizeof(uint32_t); i++)
	{
		num[i] = ((num[i] >> 24) & 0xff) |
				 ((num[i] >> 8) & 0xff00) |
				 ((num[i] << 8) & 0xff0000) |
				 ((num[i] << 24) & 0xff000000);
	}
}

/**
 * convert_endian_64 - converts 64-bit ELF data
 * @data: pointer to the data
 * @size: size of the data
*/
void convert_endian_64(void *data, size_t size)
{
	uint64_t *num = data;
	size_t i;

	for (i = 0; i < size / sizeof(uint64_t); i++)
	{
		num[i] = ((num[i] >> 56) & 0xff) |
				 ((num[i] >> 40) & 0xff00) |
				 ((num[i] >> 24) & 0xff0000) |
				 ((num[i] >> 8) & 0xff000000) |
				 ((num[i] << 8) & 0xff00000000) |
				 ((num[i] << 24) & 0xff0000000000) |
				 ((num[i] << 40) & 0xff000000000000) |
				 ((num[i] << 56) & 0xff00000000000000);
	}
}
