#include "signals.h"

/**
 * current_handler_signal - retrieves the current handler of the signal SIGINT
 * Return: pointer to current handler of SIGINT, or NULL on failure
 */
void (*current_handler_signal(void))(int)
{
	void (*current_handler)(int) = signal(SIGINT, SIG_IGN);

	if (signal(SIGINT, current_handler) == SIG_ERR)
	{
		return (NULL);
	}
	return (current_handler);
}
