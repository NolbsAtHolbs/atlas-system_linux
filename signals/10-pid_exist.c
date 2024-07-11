#include <signal.h>
#include <sys/types.h>

/**
 * pid_exist - Checks if process with provided PID exists
 * @pid: PID of process to check
 * Return: 1 if the process exists, 0 otherwise
 */
int pid_exist(pid_t pid)
{
	return (kill(pid, 0) == 0);
}
