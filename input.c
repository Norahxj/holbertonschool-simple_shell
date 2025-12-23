#include "shell.h"

/**
 * read_line - Reads a line of input from the user
 *
 * Return: pointer to the input string (must be freed by caller)
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	read = getline(&line, &len, stdin);
	if (read == -1)
	{
		free(line);
		exit(0);
	}

	line[read - 1] = '\0';
	return (line);
}
