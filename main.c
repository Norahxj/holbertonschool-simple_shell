#include "shell.h"

/**
 * main - Simple UNIX command line interpreter
 *
 * Return: Always 0
 */
int main(void)
{
	char *line;
	char **args;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		line = read_input();
		if (!line)
			break;

		args = split_line(line);
		if (args && args[0])
			execute_command(args);

		free_args(args);
		free(line);
	}

	return (0);
}
