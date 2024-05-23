#include "hls.h"
/**
 * count_files_and_folders - Counts the number of file or folder arguments
 * @argc: Number of arguments
 * @argv: Array of arguments
 * @start: Index to start checking from
 *
 * Return: Number of file or folder arguments
 */
int count_files_and_folders(int argc, char *argv[], int start)
{
    int i;
    int count;
    count = 0;
    for (i = start; i < argc; i++)
    {
        if (!is_option(argv[i], "-1"))
        {
            count++;
        }
    }
    return (count);
}
/**
 * sort_paths - Sorts the paths for directory listing priority
 * @argc: Number of arguments
 * @argv: Array of arguments
 * @start: Index to start sorting from
 */
void sort_paths(int argc, char *argv[], int start)
{
    int i;
	int j;
	char *temp;
    for (i = start; i < argc - 1; i++)
    {
        for (j = i + 1; j < argc; j++)
        {
            if ((!is_option_multiple(argv[i], "-1")) &&
				(!is_option_multiple(argv[j], "-1")))
            {
                if (compare_paths(argv[i], argv[j]) > 0)
                {
                    temp = argv[i];
                    argv[i] = argv[j];
                    argv[j] = temp;
                }
            }
        }
    }
}
/**
 * compare_paths - Simple comparison of two paths to ensure parent paths come first
 * @a: First path
 * @b: Second path
 *
 * Return: Negative if a < b, zero if a == b, positive if a > b
 */
int compare_paths(char *a, char *b)
{
    while (*a && *b)
    {
        if (*a < *b)
        {
            return (-1);
        }
        if (*a > *b)
        {
            return (1);
        }
        a++;
        b++;
    }
    if (*a == '\0' && *b == '\0')
    {
        return (0);
    }
    if (*a == '\0')
    {
        return (-1);
    }
    return (1);
}