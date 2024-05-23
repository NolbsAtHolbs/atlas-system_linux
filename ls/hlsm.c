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
	int single_column = 0;
	int start = 1;
	int file_count = 0;

	process_arguments(argc, argv, &single_column, &start);
	file_count = count_files_and_folders(argc, argv, start);

	if (file_count == 0)
	{
		list_directory(".", argv[0], single_column);
	}
	else
	{
		sort_paths(argc, argv, start);
		list_files(argc, argv, start);
		list_directories(argc, argv, start, single_column, argv[0]);
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
		if (is_option_multiple(argv[i], "-1"))
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
* is_option_multiple - Checks if argument is valid -1 option
* @arg: The argument to check
* @option: The option to check for (e.g., "-1")
*
* Return: 1 if the argument matches the option, 0 otherwise
*/
int is_option_multiple(char *arg, const char *option)
{
	int i = 0;

	if (arg[i] != '-' || option[i] != '-')
		return (0);

	i++;
	while (arg[i] != '\0' && option[1] != '\0' && arg[i] == option[1])
	{
		i++;
	}

	if (arg[i] == '\0')
	{
		return (1);
	}
	return (0);
}
