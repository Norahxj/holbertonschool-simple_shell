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
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free_args(args);
				free(line);
				return (last_status);
			}
			if (strcmp(args[0], "env") == 0)
			{
				print_env();
				last_status = 0;
			}
			else
			{
				execute_command(args);
			}
		}

		free_args(args);
		free(line);
	}
	return (last_status);
}
