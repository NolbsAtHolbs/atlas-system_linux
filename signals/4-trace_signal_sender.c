#include "signals.h"

/**
 * sigquit_halfler - Signal handler for SIGQUIT
 * @sn: Signal number
 * @si: Pointer to siginfo_t structure containing signal info
 * @foo: Pointer that does nothing
 */
void sigquit_halfler(int sn, siginfo_t *si, void *foo)
{
	(void)sn;
	(void)foo;
	printf("SIGQUIT sent by %d\n", si->si_pid);
	fflush(stdout);
}

/**
 * trace_signal_sender - Sets a handler for signal SIGQUIT using sigaction
 * Return: 0 on success, -1 on error
 */
int trace_signal_sender(void)
{
	struct sigaction sav;

	sav.sa_sigaction = sigquit_halfler;
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
