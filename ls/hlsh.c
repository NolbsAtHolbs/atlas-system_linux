#include "hls.h"

/**
* handle_errors - Prints error messages
* @program_name: Name of the program for errors (argv[0])
* @path: Path that caused the error
*/
void handle_errors(char *program_name, char *path)
{
	fprintf(stderr, "%s: cannot ", program_name);
	if (errno == ENOENT)
	{
		fprintf(stderr, "access %s: ", path);
	}
	else
	{
		fprintf(stderr, "open directory %s: ", path);
	}
	perror("");
}

/**
* my_strdup - Duplicates a string
* @s: String to duplicate
* @program_name: Name of the program for error messages
*
* Return: Pointer to duplicated string
*/
char *my_strdup(const char *s, char *program_name)
{
	int len = 0;
	char *dup;
	int i;

	while (s[len] != '\0')
		len++;

	dup = (char *)malloc(len + 1);
	if (dup == NULL)
	{
		handle_errors(program_name, "memory allocation");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i <= len; i++)
	{
		dup[i] = s[i];
	}

	return (dup);
}

/**
* xmalloc - Allocates memory and checks for allocation errors
* @size: Size of memory to allocate
* @program_name: Name of the program for error messages
*
* Return: Pointer to allocated memory
*/
void *xmalloc(size_t size, char *program_name)
{
	void *ptr = malloc(size);

	if (!ptr)
	{
		handle_errors(program_name, "memory allocation");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

/**
* xrealloc - Reallocates memory and checks for allocation errors
* @ptr: Pointer to previously allocated memory
* @size: New size of memory
* @program_name: Name of the program for error messages
*
* Return: Pointer to reallocated memory
*/
void *xrealloc(void *ptr, size_t size, char *program_name)
{
	ptr = realloc(ptr, size);
	if (!ptr)
	{
		handle_errors(program_name, "memory allocation");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

/**
* compare_strings - Case insensitive string compare
* @a: First string
* @b: Second string
*
* Return: Neg val if a < b, 0 if a == b, pos val if a > b
*/
int compare_strings(const char *a, const char *b)
{
	char lower_a;
	char lower_b;

	while (*a && *b)
	{
		lower_a = (*a >= 'A' && *a <= 'Z') ? *a + 32 : *a;
		lower_b = (*b >= 'A' && *b <= 'Z') ? *b + 32 : *b;

		if (lower_a < lower_b)
			return (-1);
		if (lower_a > lower_b)
			return (1);

		a++;
		b++;
	}
	if (*a == '\0' && *b == '\0')
		return (0);
	if (*a == '\0')
		return (-1);
	return (1);
}
