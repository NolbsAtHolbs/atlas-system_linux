#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

void list_directory(char *path, char *program_name);
void handle_errors(char *program_name, char *path);

/**
* main - main program
* @argc: Number of arguments
* @argv: Array of arguments
*
* Return: 0 on success, otherwise err code
*/
int main(int argc, char *argv[])
{
	int i;

	/* list current dir */
	if (argc == 1)
	{
		list_directory(".", argv[0]);
	}
	else
	{
		for (i = 1; i < argc; i++)
		{
			list_directory(argv[i], argv[0]);
			if (i < argc - 1)
			{
				printf("\n");
			}
		}
	}
	return (0);
}

/**
* list_directory - Lists the contents of a directory
* @path: Path to the directory
* @program_name: Name of the program (argv[0])
*/
void list_directory(char *path, char *program_name)
{
	struct dirent *entry;
	DIR *dir;

	dir = opendir(path);
	if (dir == NULL)
	{
		handle_errors(program_name, path);
		return;
	}
	printf("%s:\n", path);
	while ((entry = readdir(dir)) != NULL)
	{
		printf("%s\n", entry->d_name);
	}
	closedir(dir);
}

/**
* handle_errors - Prints error messages
* @program_name: Name of the program for errors (argv[0])
* @path: Path that caused the error
*/
void handle_errors(char *program_name, char *path)
{
	fprintf(stderr, "%s: cannot access '%s': ", program_name, path);
	perror("");
}
