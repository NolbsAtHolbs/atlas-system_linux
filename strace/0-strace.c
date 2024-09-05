#include "syscalls.h"
/**
 * main - Executes and traces a given command, and prints a syscall number
 * @argc: number of args passed to the program
 * @argv: the arguments to be assessed
 * @envvar: the environmental variable to check within
 * Return: 0 on success, else 1
 */
int main(int argc, char *argv[], char *envvar[])
{
	pid_t pid;
	int status = 0;
	int alt = 0;
	struct user_regs_struct regs;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
		return (1);
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		/* Child process: prepare for tracing and execute the command */
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		kill(getpid(), SIGSTOP);  /* Stop to be traced by the parent */
		execve(argv[1], &argv[1], envvar);  /* Execute the command at second address */
		perror("execve");  /* If execve fails */
		exit(1);
	}
	else
	{
		/* Parent process: trace system calls */
		while (1)
		{
			wait(&status);  /* Wait for child to stop or exit */

			if (WIFEXITED(status))  /* If the child exits */
				break;

			if (!ptrace(PTRACE_GETREGS, pid, NULL, &regs) && alt)
				printf("%llu\n", (unsigned long long)regs.orig_rax);  /* Print syscall number */

			ptrace(PTRACE_SYSCALL, pid, NULL, NULL);  /* Continue tracing */
			alt = !alt;  /* Alternate between syscall entry and exit */
		}
	}

	return (0);
}
