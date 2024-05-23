#include "hls.h"

/**
* list_directory - Lists the contents of a directory
* @path: Path to the directory
* @program_name: Name of the program (argv[0])
* @single_column: Flag indicating if output should be single column
*/
void list_directory(char *path, char *program_name, int single_column)
{
	DIR *dir;
	char **entries;
	int count;
	int i;

	if (single_column)
	{

	}

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

	for (i = 0; i < count; i++)
	{
		printf("%s\n", entries[i]);
		free(entries[i]);
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
	return (entries);
}
