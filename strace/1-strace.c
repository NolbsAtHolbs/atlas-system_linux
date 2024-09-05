#include "syscalls.h"
/**
 * main - Executes and traces a given command, and prints a syscall name
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
		ptrace(PTRACE_TRACEME, 0, NULL, NULL); /* Child process: execute the command and allow tracing */
		execve(argv[1], &argv[1], envvar);
	}
	else
	{
		while (1) /* Parent process: trace system calls */
		{
			ptrace(PTRACE_SYSCALL, child, NULL, NULL);
			wait(&status);
			if (WIFEXITED(status))
				break;

			ptrace(PTRACE_GETREGS, child, NULL, &regs); /* Get system call details */
			unsigned long syscall_num = regs.orig_rax;

			if (syscall_num < sizeof(syscalls_64_g) / sizeof(syscall_t) &&
				syscalls_64_g[syscall_num].name) /* Check for valid syscall number */
			{
				if (entry_exit_toggle == 0 || entry_exit_toggle % 2 != 0) /* entry or exit */
				{
					if (syscall_num != 1) /* Syscall not 'write' */
						fprintf(stderr, "%s\n", SYSNAME);
					else
						fprintf(stderr, "%s", SYSNAME);
				}
				if (entry_exit_toggle % 2 == 0 && syscall_num == 1)
					fprintf(stderr, "\n");
			}
			else
			{
				fprintf(stderr, "unknown_syscall\n");
			}

			entry_exit_toggle++;
		}
	}
	return (EXIT_SUCCESS);
}
