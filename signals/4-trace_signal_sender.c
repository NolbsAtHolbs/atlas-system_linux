#include "signals.h"

/**
 * sigquit_handler - Signal handler for SIGQUIT
 * @sn: Signal number
 * @info: Pointer to siginfo_t structure containing signal information
 */
void sigquit_handler(int sn, siginfo_t *info)
{
	if (sn == SIGQUIT)
	{
		printf("SIGQUIT sent by %d\n", info->si_pid);
		fflush(stdout);
	}
}

/**
 * trace_signal_sender - Sets a handler for signal SIGQUIT using sigaction
 * Return: 0 on success, -1 on error
 */
int trace_signal_sender(void)
{
	struct sigaction sav;

	sav.sa_sigaction = sigquit_handler;
	sav.sa_flags = SA_SIGINFO;
	sigemptyset(&sav.sa_mask);

	if (sigaction(SIGQUIT, &sav, NULL) == -1)
	{
		return (-1);
	}
	else
	{
		return (0);
	}
}
