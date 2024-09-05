#include "syscalls.h"
/**
 * main - Executes and traces a given command, and prints a syscall number
 * @argc: number of args passed to the program
 * @argv: the arguments to be assessed
 * @envvar: the environmental variable to check within
 * Return: 0 on success, else 1
 */
int main(int argc, const char *argv[], char *const envp[])
{
    pid_t child;
    int status;
    int print_on_entry = 1;  /* Toggle to print only on syscall entry */
    struct user_regs_struct regs;

    if (argc < 2)
    {
        fprintf(stderr, "Unsupported number of Arguments\n");
        return (EXIT_FAILURE);
    }

    child = fork();
    if (child == -1)
    {
        perror("fork failed");
        return (EXIT_FAILURE);
    }

    if (child == 0)  /* Child process */
    {
        if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
        {
            perror("ptrace(PTRACE_TRACEME) failed");
            exit(EXIT_FAILURE);
        }
        execve(argv[1], (char * const *)(argv + 1), envp);
        perror("execve failed");  /* This will only run if execve fails */
        exit(EXIT_FAILURE);
    }
    else  /* Parent process */
    {
        while (1)
        {
            if (ptrace(PT_SYSCALL, child, NULL, NULL) == -1)
            {
                perror("ptrace(PT_SYSCALL) failed");
                exit(EXIT_FAILURE);
            }

            wait(&status);  /* Wait for child process to change state */

            if (WIFEXITED(status))  /* If child has exited, break loop */
                break;

            if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
            {
                perror("ptrace(PTRACE_GETREGS) failed");
                exit(EXIT_FAILURE);
            }

            if (print_on_entry)
                fprintf(stderr, "%lu\n", (size_t)regs.orig_rax);  /* Print syscall number */

            print_on_entry = !print_on_entry;  /* Toggle between entry and exit */
        }
    }

    return (EXIT_SUCCESS);
}