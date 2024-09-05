#include "syscalls.h"
/**
 * main - Executes and traces a given command, and prints a syscall number
 * @argc: number of args passed to the program
 * @argv: the arguments to be assessed
 * @envvar: the environmental variable to check within
 * Return: success on success, else failure
 */
int main(int argc, char *argv[], char *envvar[])
{
	pid_t child;
	int status;
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
				syscalls_64_g[syscall_num].name) /* Print syscall name if valid */
			{
				printf("%s\n", syscalls_64_g[syscall_num].name);
			}
			else
			{
				printf("unknown_syscall\n");
			}
		}
	}
	return (EXIT_SUCCESS);
}
