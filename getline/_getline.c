#include "_getline.h"

/**
 * _getline - reads a line from a file descriptor
 * @fd: a file descriptor
 * Return: null terminated string, or NULL if error or no line
*/

char *_getline(const int fd)
{
	static char buffer[READ_SIZE + 1]; /* account for null terminator */
	static int position;
	static int bytes_read;
	char *line = NULL;
	int i = position;
	int j;

	while (1)
	{
		if (position >= bytes_read)
		{
			position = 0;
			bytes_read = read(fd, buffer, READ_SIZE);
			if (bytes_read == 0)
			{
				if (i < position)
				{
					line = malloc((position - i + 1) * sizeof(char));
					if (!line)
						return (NULL);
					for (j = i; j < position; j++)
						line[j - i] = buffer[j];
					line[position - i] = '\0';
					position++;
					return (line);
				}
                else
                {
                    return (NULL);
                }
			}
			if (bytes_read == -1) /* account for _getline read error */
				return (NULL);
			buffer[bytes_read] = '\0'; /* mark end of string */
		}
		if (buffer[position] == '\n')
		{
			line = malloc((position - i + 1) * sizeof(char));
			if (!line)
				return (NULL);
			for (j = i; j < position; j++)
				line[j - i] = buffer[j]; /* copy buffer array to line array */
			line[position - i] = '\0';
			position++;
			return (line);
		}
		position++;
	}
	return (NULL);
}
