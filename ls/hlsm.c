#include "hls.h"

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
	int single_column = 0;
	int start = 1;
	int file_count = 0;
	DIR *dir;

	process_arguments(argc, argv, &single_column, &start);
	for (i = start; i < argc; i++)
	{
		if (!is_option(argv[i], "-1"))
			file_count++;
	}

	if (file_count == 0)
		list_directory(".", argv[0], single_column);
	else
	{
		for (i = start; i < argc; i++)
		{
			if (is_option(argv[i], "-1"))
				continue;

			dir = opendir(argv[i]);
			if (dir == NULL && errno != ENOTDIR)
			{
				handle_errors(argv[0], argv[i]);
				continue;
			}
			if (dir != NULL)
				closedir(dir);

			if (file_count > 1 && dir != NULL)
				printf("%s:\n", argv[i]);

			list_directory(argv[i], argv[0], single_column);
		}
	}
	return (0);
}

/**
* process_arguments - Processes command-line arguments
* @argc: Number of arguments
* @argv: Array of arguments
* @single_column: Pointer to the single column flag
* @start: Pointer to the start index
*/
void process_arguments(int argc, char *argv[], int *single_column, int *start)
{
	int i;

	for (i = 1; i < argc; i++)
	{
		if (is_option(argv[i], "-1"))
		{
			*single_column = 1;
			(*start)++;
		}
		else
		{
			break;
		}
	}
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
