#include "signals.h"

/**
 * current_handler_sigaction - Retrieves current handler of SIGINT
 * Return: Pointer to current handler of SIGINT, or NULL on failure
 */
void (*current_handler_sigaction(void))(int)
{
	struct sigaction sigactvar;

	if (sigaction(SIGINT, NULL, &sigactvar) == -1)
	{
		return (NULL);
	}
	else
	{
		return (sigactvar.sa_handler); /* function pointer */
	}
}
