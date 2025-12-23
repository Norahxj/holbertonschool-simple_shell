#include "shell.h"
/**
 * main - Simple UNIX command line interpreter
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}

		line[read - 1] = '\0';

		pid = fork();
		if (pid == 0)
		{
			if (execve(line, (char *const[])
						{line, NULL}, environ) == -1)
			{
				perror("./shell");
				exit(1);
			}
		}
		else if (pid > 0)
		{
			wait(&status);
		}
		else
		{
			perror("fork");
		}
	}
	free(line);
	return (0);
}
