#include "shell.h"

/**
 * execute_command - Executes a single command using fork and execve
 * @line: command to execute
 *
 * Return: void
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *args[2];

	pid = fork();
	if (pid == 0)
	{
		args[0] = line;
		args[1] = NULL;
		if (execve(line, args, environ) == -1)
		{
			perror("./shell");
			exit(1);
		}
	}
	else if (pid > 0)
		wait(&status);
	else
		perror("fork");
}
