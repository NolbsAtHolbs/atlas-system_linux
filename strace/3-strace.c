#include "syscalls.h"
/**
 * main - executes and traces a given command, printing syscall names, their parameters, & return values.
 * @argc: number of args passed to the program
 * @argv: the arguments to be assessed
 * @envvar: the environmental variable to check within
 * Return: success on success, else failure
 */
int main(int argc, char *argv[], char *envvar[])
{
	pid_t child;
	int status = 0;
	struct user_regs_struct regs;

	if (argc < 2)
	{
		fprintf(stderr, "Unsupported number of arguments\n");
		return (EXIT_FAILURE);
	}

	child = fork();
	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL); /* Child process: execute command */
		execve(argv[1], &argv[1], envvar);
	}
	else
	{
		while (1)
		{
			ptrace(PTRACE_SYSCALL, child, NULL, NULL);
			wait(&status);
			if (WIFEXITED(status))
			{
				fprintf(stderr, " = ?\n");
				break;
			}

			ptrace(PTRACE_GETREGS, child, NULL, &regs); /* Get registers, which contain syscall number, parameters, return value */

			unsigned long syscall_num = regs.orig_rax; /* Retrieve syscall name */
			const char *syscall_name = "unknown_syscall";
			if (syscall_num < SYS_CALL_COUNT && SYSNAME != NULL)
			{
				syscall_name = SYSNAME;
			}

			fprintf(stderr, "%s(", syscall_name); /* Print syscall name and its parameters in hexadecimal */
			fprintf(stderr, "%#lx, %#lx, %#lx", 
				(size_t)(regs.rdi == 0 ? 0 : regs.rdi),
				(size_t)(regs.rsi == 0 ? 0 : regs.rsi),
				(size_t)(regs.rdx == 0 ? 0 : regs.rdx));

			if (regs.rax == 0)
				fprintf(stderr, ") = 0\n");
			else
				fprintf(stderr, ") = %#lx\n", (size_t)regs.rax);
		}
	}
	return (EXIT_SUCCESS);
}