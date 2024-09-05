#include "multithreading.h"

/**
 * prime_factors - Factorizes a number into a list of prime factors
 * @s: String representation of the number to factorize
 * Return: A pointer to the list of prime factors
 */
list_t *prime_factors(char const *s)
{
	unsigned long num, *temp, prime = 2;
	char *endptr;
	list_t *prime_list = malloc(sizeof(list_t));

	if (!prime_list)
		return (NULL); /* Handle memory allocation failure */

	/* Convert the input string to an unsigned long */
	num = strtoul(s, &endptr, 10);
	if (*endptr != '\0') /* Check if the string is a valid number */
	{
		free(prime_list);
		return (NULL); /* Invalid input */
	}

	list_init(prime_list);

	/* Factorize by dividing the number by primes starting from 2 */
	while (prime * prime <= num)
	{
		while (num % prime == 0)
		{
			temp = malloc(sizeof(unsigned long));
			if (!temp)
			{
				list_destroy(prime_list, free); /* Clean up */
				free(prime_list);
				return (NULL); /* Memory allocation failure */
			}
			*temp = prime;
			list_add(prime_list, temp);
			num /= prime;
		}

		prime += 1 + (prime != 2); /* Move to the next prime (skip even numbers) */
	}

	/* If there's a prime factor greater than sqrt(num), add it */
	if (num >= 2)
	{
		temp = malloc(sizeof(unsigned long));
		if (!temp)
		{
			list_destroy(prime_list, free);
			free(prime_list);
			return (NULL); /* Memory allocation failure */
		}
		*temp = num;
		list_add(prime_list, temp);
	}

	return (prime_list); /* Return the list of prime factors */
}
