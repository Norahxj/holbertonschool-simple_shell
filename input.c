#include "shell.h"

/**
 * read_input - Reads a line from stdin
 *
 * Return: Pointer to input line or NULL
 */
char *read_input(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	read = getline(&line, &len, stdin);
	if (read == -1)
	{
		free(line);
		return (NULL);
	}

	if (line[read - 1] == '\n')
		line[read - 1] = '\0';

	return (line);
}

/**
 * split_line - Splits line into arguments
 * @line: Input line
 *
 * Return: Array of strings
 */
char **split_line(char *line)
{
	char **args;
	char *token;
	int i = 0;

	args = malloc(sizeof(char *) * 64);
	if (!args)
		return (NULL);

	token = strtok(line, " \t");
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	return (args);
}

/**
 * free_args - Frees argument array
 * @args: Array of arguments
 */
void free_args(char **args)
{
	if (args)
		free(args);
}
