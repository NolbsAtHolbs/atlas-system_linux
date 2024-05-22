#include "hls.h"

void list_directory(char *path, char *program_name, int single_column);
char **read_entries(DIR *dir, int *count, char *program_name);
int is_option(char *arg, const char *option);

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
	int first = 1;
	int single_column = 0;

	if (argc > 1 && is_option(argv[1], "-1"))
	{
		single_column = 1;
		argv++;
		argc--;
	}

	if (argc == 1)
	{
		list_directory(".", argv[0], single_column);
	}
	else
	{
		for (i = 1; i < argc; i++)
		{
			DIR *dir = opendir(argv[i]);
			if (dir == NULL && errno != ENOTDIR)
			{
				handle_errors(argv[0], argv[i]);
				continue;
			}
			if (dir != NULL)
			{
				closedir(dir);
			}

			if (argc > 2 && dir != NULL)
			{
				if (!first)
				{
					printf("\n");
				}
				printf("%s:\n", argv[i]);
				first = 0;
			}

			list_directory(argv[i], argv[0], single_column);
		}
	}
	return (0);
}

/**
 * is_option - Checks if an argument is an option
 * @arg: The argument to check
 * @option: The option to check for
 *
 * Return: 1 if the argument matches the option, 0 otherwise
 */
int is_option(char *arg, const char *option)
{
	int i = 0;

	while (arg[i] != '\0' && option[i] != '\0' && arg[i] == option[i])
	{
		i++;
	}

	if (arg[i] == '\0' && option[i] == '\0')
	{
		return (1);
	}

	return (0);
}

/**
* list_directory - Lists the contents of a directory
* @path: Path to the directory
* @program_name: Name of the program (argv[0])
* @single_column: Flag for single column output
*/
void list_directory(char *path, char *program_name, int single_column)
{
	DIR *dir;
	char **entries;
	int count;

	dir = opendir(path);
	if (dir == NULL)
	{
		if (errno == ENOTDIR)
		{
			printf("%s\n", path);
			return;
		}
		handle_errors(program_name, path);
		return;
	}

	entries = read_entries(dir, &count, program_name);
	closedir(dir);

	sort_entries(entries, count);

	if (single_column)
	{
		for (count = 0; entries[count] != NULL; count++)
		{
			printf("%s\n", entries[count]);
			free(entries[count]);
		}
	}
	else
	{
		for (count = 0; entries[count] != NULL; count++)
		{
			printf("%s\n", entries[count]);
			free(entries[count]);
		}
	}
	free(entries);
}

/**
* read_entries - Reads directory entries into an array
* @dir: Directory stream
* @count: Pointer to count of entries
* @program_name: Name of the program for error messages
*
* Return: Array of entries
*/
char **read_entries(DIR *dir, int *count, char *program_name)
{
	struct dirent *entry;
	char **entries;
	int size;

	entries = xmalloc(10 * sizeof(char *), program_name);
	size = 10;
	*count = 0;

	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			if (*count >= size)
			{
				size *= 2;
				entries = xrealloc(entries, size * sizeof(char *), program_name);
			}
			entries[*count] = my_strdup(entry->d_name, program_name);
			(*count)++;
		}
	}
	entries[*count] = NULL;
	return (entries);
}
