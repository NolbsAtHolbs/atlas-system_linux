#include "hls.h"

/**
* sort_entries - Bubble sorts an array of strs
* @entries: Array of strings
* @count: Number of strings in array
*/
void sort_entries(char **entries, int count)
{
	int i;
	int j;
	int swapped;
	char *temp;

	for (i = 0; i < count - 1; i++)
	{
		swapped = 0;
		for (j = 0; j < count - i - 1; j++)
		{
			if (compare_strings(entries[j], entries[j + 1]) > 0)
			{
				temp = entries[j];
				entries[j] = entries[j + 1];
				entries[j + 1] = temp;
				swapped = 1;
			}
		}
		if (!swapped)
			break;
	}
}