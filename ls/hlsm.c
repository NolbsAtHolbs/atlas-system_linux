#include "hls.h"

void list_directory(char *path, char *program_name);
char **read_entries(DIR *dir, int *count, char *program_name);

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

	if (argc == 1)
	{
		list_directory(".", argv[0]);
	}
	else
	{
		for (i = 1; i < argc; i++)
		{
			if (argc > 2)
			{
				printf("%s:\n", argv[i]);
			}
			list_directory(argv[i], argv[0]); /* curious */
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
* @show_path: Flag indicating when path is shown
*/
void list_directory(char *path, char *program_name)
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

	for (count = 0; entries[count] != NULL; count++)
	{
		printf("%s\n", entries[count]);
		free(entries[count]);
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
