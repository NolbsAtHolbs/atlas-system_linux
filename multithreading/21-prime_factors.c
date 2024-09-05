#include "multithreading.h"

list_t *create_prime_list(char const *s);
int add_prime_factors(list_t *prime_list, unsigned long *num);
int add_remaining_prime(list_t *prime_list, unsigned long num);

/**
 * prime_factors - Factorizes a number into a list of prime factors
 * @s: String representation of the number to factorize
 * Return: A pointer to the list of prime factors
 */
list_t *prime_factors(char const *s)
{
	unsigned long num;
	list_t *prime_list = create_prime_list(s);

	if (!prime_list)
		return (NULL); /* Handle invalid input or memory allocation failure */

	num = strtoul(s, NULL, 10);
	if (add_prime_factors(prime_list, &num) == -1)
	{
		list_destroy(prime_list, free);
		free(prime_list);
		return (NULL);
	}

	if (add_remaining_prime(prime_list, num) == -1)
	{
		list_destroy(prime_list, free);
		free(prime_list);
		return (NULL);
	}

	return (prime_list); /* Return the list of prime factors */
}

/**
 * create_prime_list - Initializes the prime list
 * @s: String representation of the number
 * Return: A pointer to the initialized prime list or NULL on failure
 */
list_t *create_prime_list(char const *s)
{
	list_t *prime_list = malloc(sizeof(list_t));

	if (!prime_list || *s == '\0')
	{
		free(prime_list);
		return (NULL); /* Handle memory allocation failure or invalid input */
	}
	list_init(prime_list);
	return (prime_list);
}

/**
 * add_prime_factors - Adds prime factors to the list
 * @prime_list: The list of prime factors
 * @num: Pointer to the number being factorized
 * Return: 0 on success, -1 on failure
 */
int add_prime_factors(list_t *prime_list, unsigned long *num)
{
	unsigned long prime = 2;
	unsigned long *temp;

	while (prime * prime <= *num)
	{
		while (*num % prime == 0)
		{
			temp = malloc(sizeof(unsigned long));
			if (!temp)
				return (-1); /* Memory allocation failure */

			*temp = prime;
			list_add(prime_list, temp);
			*num /= prime;
		}
		prime += 1 + (prime != 2); /* Skip even numbers after 2 */
	}
	return (0);
}

/**
 * add_remaining_prime - Adds remaining prime factor greater than sqrt(num)
 * @prime_list: The list of prime factors
 * @num: The remaining number
 * Return: 0 on success, -1 on failure
 */
int add_remaining_prime(list_t *prime_list, unsigned long num)
{
	unsigned long *temp;

	if (num >= 2)
	{
		temp = malloc(sizeof(unsigned long));
		if (!temp)
			return (-1); /* Memory allocation failure */

		*temp = num;
		list_add(prime_list, temp);
	}
	return (0);
}
