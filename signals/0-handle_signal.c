#include "signals.h"

/**
 * signal_interrupt_handler - Handles the signal-interrupt signal
 * @signum: Signal number
 */
void signal_interrupt_handler(int signalnumber)
{
	printf("Gotcha! [%d]\n", signalnumber); // Expecting portable number 2
	fflush(stdout);	// Immediately flush output to console
}

/**
 * handle_signal_error - Returns exit codes for sigint confirmation
 *
 * Return: 0 on success, -1 on error
 */
int handle_signal_error(void)
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
