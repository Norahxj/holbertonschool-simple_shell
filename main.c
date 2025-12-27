#include "shell.h"

/**
 * main - Simple shell entry point
 *
 * Return: Always 0
 */
char *prog_name;
unsigned int line_number = 0;
int last_status = 0;

int main(int argc, char **argv)
{
	char *line;
	char **args;

	(void)argc;
	prog_name = argv[0];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		line = read_input();
		if (!line)
			break;

		line_number++;

		args = split_line(line);
		if (args && args[0])
			execute_command(args);

		free_args(args);
		free(line);
	}
	return (last_status);
}
