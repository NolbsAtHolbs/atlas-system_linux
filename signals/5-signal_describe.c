#include "signals.h"

/**
 * _signal_describe - Prints description of given signal
 * @argc: Argument count
 * @argv: Array containing strings of values of signals to describe
 * Return: EXIT_SUCCESS upon success, EXIT_FAILURE upon incorrect argument supplied
 */
int _signal_describe(int argc, char **argv)
{
	int sn;

	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	sn = atoi(argv[1]);

	if (sn > 0 && sn < NSIG) /* checking range with macro */
	{
		printf("%d: %s\n", sn, strsignal(sn));
	}
	else
	{
		printf("%d: Unknown signal %d\n", sn, sn);
	}
	return (EXIT_SUCCESS);
}
