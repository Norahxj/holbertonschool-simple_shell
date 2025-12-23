#include "shell.h"

/**
 * execute_command - Executes a command
 * @args: Argument list
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
			perror("./shell");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		wait(&status);
	}
}

/**
 * free_args - Frees argument array
 * @args: Argument list
 */
void free_args(char **args)
{
	free(args);
}
