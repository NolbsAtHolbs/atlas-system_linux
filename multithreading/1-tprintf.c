#include "multithreading.h"
/**
 * tprintf - prints a formatted string prefixed by the thread ID
 * @format: the format string
 * Return: the number of characters printed
 */
int tprintf(char const *format, ...)
{
	pthread_t pts = pthread_self();

	printf("[%lu] %s", pts, format);
	return (0);
}
