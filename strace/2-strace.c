#include "syscalls.h"
/**
 * main - Executes and traces a given command, and prints its name and return value in hex
 * @argc: number of args passed to the program
 * @argv: the arguments to be assessed
 * @envvar: the environmental variable to check within
 * Return: success on success, else failure
 */
int main(int argc, char *argv[], char *envvar[])
{
	pid_t child;
	int status = 0;
	int entry_exit_toggle = 0;
	struct user_regs_struct regs;

	if (argc < 2)
	{
		fprintf(stderr, "Unsupported number of arguments\n");
		return (EXIT_FAILURE);
	}

	child = fork();
	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, child, NULL, NULL);
		execve(argv[1], &argv[1], envvar);
	}
	else
	{
		while (1)
		{
			ptrace(PT_SYSCALL, child, NULL, NULL);
			wait(&status);
			ptrace(PTRACE_GETREGS, child, NULL, &regs);
			if (WIFEXITED(status))
			{
				fprintf(stderr, " = ?\n");
				break;
			}
			if (entry_exit_toggle == 0 || entry_exit_toggle % 2 != 0)
				fprintf(stderr, "%s", SYSNAME);
			if (entry_exit_toggle % 2 == 0)
			{
				if (regs.orig_rax != 1)
					fprintf(stderr, " = %#lx\n", (size_t)regs.rax);
				else
					fprintf(stderr, " = %#lx\n", (size_t)regs.rax);
			}
			entry_exit_toggle++;
		}
	}
	return (EXIT_SUCCESS);
}
