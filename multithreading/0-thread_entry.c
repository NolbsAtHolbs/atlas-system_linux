#include "multithreading.h"
/**
 * thread_entry - Entry point for a new thread that prints a string
 * @arg: holds the address of the string to be printed
 * Return: NULL
 */
void *thread_entry(void *arg)
{
	printf("%s\n", (char *)arg);
	pthread_exit(NULL);
}
