#include "signals.h"

/**
 * sigint_tel - Handles SIGINT catch
 * @sn: Signal number
 */
void sigint_tel(int sn)
{
	printf("Caught %d\n", sn);
	printf("Signal received\n");
	fflush(stdout);
}

/**
 * main - Sets a handler for SIGINT and suspends the program
 * Return: EXIT_SUCCESS on successful execution
 */
int main(void)
{
	struct sigaction sav;

	sav.sa_handler = sigint_tel;
	sigemptyset(&sav.sa_mask);
	sav.sa_flags = 0;

	if (sigaction(SIGINT, &sav, NULL) == -1)
	{
		perror("sigaction");
		return (EXIT_FAILURE);
	}
	pause();
	return (EXIT_SUCCESS);
}
