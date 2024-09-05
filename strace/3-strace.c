#include "syscalls.h"

void print_params(size_t i, struct user_regs_struct *regs);

/**
 * main - executes and traces a given command, and prints a syscall name, params, and return value
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
	size_t i = 0;
	struct user_regs_struct regs;

	if (argc < 2)
	{
		fprintf(stderr, "Unsupported number of arguments\n");
		return (-1);
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
				fprintf(stderr, ") = ?\n");
				break;
			}
			if (entry_exit_toggle == 0 || entry_exit_toggle % 2 != 0)
			{
				fprintf(stderr, "%s(", SYSNAME);
				for (i = 0; i < SYSPARAM; i++)
				{
					if (SYSTYPE == VOID)
						continue;
					if (SYSTYPE == VARARGS)
						fprintf(stderr, ", ...");
					else
						print_params(i, &regs);
				}
			}
			if (entry_exit_toggle % 2 == 0)
				fprintf(stderr, ") = %#lx\n", (size_t)regs.rax);
			entry_exit_toggle++;
		}
	}
	return (0);
}
/**
 * print_params - prints system call parameters based on index
 * @i: index of the parameter to print
 * @regs: pointer to user_regs_struct containing syscall parameters
 */
void print_params(size_t i, struct user_regs_struct *regs)
{
	/* Store all the register values in an array */
	size_t params[] =
	{
		(size_t)regs->rdi,
		(size_t)regs->rsi,
		(size_t)regs->rdx,
		(size_t)regs->r10,
		(size_t)regs->r8,
		(size_t)regs->r9
	};

	if (i == 0)  /* First parameter without a preceding comma */
	{
		fprintf(stderr, "%#lx", params[i]);
	}
	else if (i < 6)  /* Subsequent parameters with a preceding comma */
	{
		fprintf(stderr, ", %#lx", params[i]);
	}
}
