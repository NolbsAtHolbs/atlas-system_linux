#include "signals.h"

/**
 * main - Sends the SIGINT signal to a process given its PID
 * @argc: Argument num passed
 * @argv: Array of strings representing args
 * Return: EXIT_SUCCESS, or EXIT_FAILURE
 */
int main(int argc, char **argv)
{
	int cnk;

	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	
	cnk = atoi(argv[1]);
	if (kill(cnk, SIGINT) == -1)
	{
		perror("kill");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
