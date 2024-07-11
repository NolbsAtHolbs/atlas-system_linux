#include "signals.h"

/**
 * signal_interrupt_handler - Handles the signal-interrupt signal
 * @portablenumber: Signal number code
 */
void signal_interrupt_handler(int portablenumber)
{
	printf("Gotcha! [%d]\n", portablenumber); /* Expecting portable number 2 */
	fflush(stdout);	/* Immediately flush output to console */
}

/**
 * handle_signal_error - Returns exit codes for sigint confirmation
 *
 * Return: 0 on success, -1 on error
 */
int handle_signal(void)
{
	if (signal(SIGINT, signal_interrupt_handler) == SIG_ERR)
	{
		return (-1);
	}
	else
	{
		return (0);
	}
}
