#include "multithreading.h"

/* Global mutex for thread synchronization */
pthread_mutex_t mutex;

/**
 * init_mutex - Constructor function to initialize the mutex
 */
__attribute__((constructor)) void init_mutex(void)
{
	pthread_mutex_init(&mutex, NULL);
}

/**
 * destroy_mutex - Destructor function to destroy the mutex
 */
__attribute__((destructor)) void destroy_mutex(void)
{
	pthread_mutex_destroy(&mutex);
}

/**
 * tprintf - Thread-safe printf function that prepends thread ID to output
 * @format: Formatted string to print
 * Return: Number of characters printed
 */
int tprintf(char const *format, ...)
{
	int ret;
	va_list args;
	pthread_t tid = pthread_self();

	pthread_mutex_lock(&mutex); /* Lock the mutex to avoid race condition */

	printf("[%lu] ", tid); /* Print thread ID */

	va_start(args, format);
	ret = vprintf(format, args); /* Print the formatted string */
	va_end(args);

	pthread_mutex_unlock(&mutex); /* Unlock the mutex after printing */

	return (ret);
}
