#include "syscalls.h"
/**
 * main - Executes and traces a given command, and prints a syscall number
 * @argc: number of args passed to the program
 * @argv: the arguments to be assessed
 * @envvar: the environmental variable to check within
 * Return: 0 on success, else -1
 */
int main(int argc, char *argv[], char *envvar[])
{
	pid_t child;
	int status, print_check = 0;
	struct user_regs_struct regs;

	if (argc < 2)
	{
		fprintf(stderr, "Unsupported number of Arguments\n");
		return (EXIT_FAILURE);
	}
	child = fork();
	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execve(argv[1], &argv[1], envvar);
	}
	else
	{
		while (1)
		{
			ptrace(PT_SYSCALL, child, NULL, NULL);
			wait(&status);
			if (WIFEXITED(status))
				break;
			ptrace(PTRACE_GETREGS, child, NULL, &regs);
			if (print_check == 0 || print_check % 2 != 0)
				fprintf(stderr, "%llu\n", (unsigned long long)regs.orig_rax);
			print_check++;
		}
	}
	return (EXIT_SUCCESS);
}
