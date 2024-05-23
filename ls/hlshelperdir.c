#include "hls.h"

/**
* list_files - Lists the files
* @argc: Number of arguments
* @argv: Array of arguments
* @start: Index to start checking from
*/
void list_files(int argc, char *argv[], int start)
{
	int i;
	DIR *dir;
	int first_file = 1;

	for (i = start; i < argc; i++)
	{
		if (is_option_multiple(argv[i], "-1"))
			continue;
		dir = opendir(argv[i]);
		if (dir == NULL && errno == ENOTDIR)
		{
			if (!first_file)
			{
				printf(" ");
			}
			printf("%s", argv[i]);
			first_file = 0;
		}
		else if (dir != NULL)
		{
			closedir(dir);
		}
	}
	if (!first_file)
	{
		printf("\n");
	}
}

/**
* list_directories - Lists the directories and their contents
* @argc: Number of arguments
* @argv: Array of arguments
* @start: Index to start checking from
* @single_column: Flag for single column output
* @program_name: Name of the program for error messages
*/
void list_directories(int argc, char *argv[], int start, int single_column, char *program_name)
{
	int i;
	DIR *dir;
	int first_dir = 1;

	for (i = start; i < argc; i++)
	{
		if (is_option_multiple(argv[i], "-1"))
			continue;
		dir = opendir(argv[i]);
		if (dir == NULL && errno != ENOTDIR)
		{
			handle_errors(program_name, argv[i]);
			continue;
		}
		if (dir != NULL)
		{
			closedir(dir);
			if (!first_dir)
			{
				printf("\n");
			}
			printf("%s:\n", argv[i]);
			first_dir = 0;
			list_directory(argv[i], program_name, single_column);
		}
	}
}
