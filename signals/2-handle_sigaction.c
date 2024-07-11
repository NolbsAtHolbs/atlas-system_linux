#include "signals.h"

/* sigint_handler - Signal handler for SIGINT
 * @signalnumber: Signal number
 */
void sigint_handler(int signalnumber)
{
	printf("Gotcha! [%d]\n", signalnumber);
	fflush(stdout);
}

/* handle_sigaction - Sets a handler for the signal SIGINT using sigaction
 *
 * Return: 0 on success, -1 on error
 */
int handle_sigaction(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		return (-1);
	}
	else
	{
		return (0);
	}
}
