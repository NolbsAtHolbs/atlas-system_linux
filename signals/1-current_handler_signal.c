#include "signals.h"

/**
 * current_handler_signal - retrieves the current handler of the signal SIGINT
 * Return: pointer to current handler of SIGINT, or NULL on failure hopefully
 */
void (*current_handler_signal(void))(int)
{
	return (signal(SIGINT, SIG_IGN));
}
