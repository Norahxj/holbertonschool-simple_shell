#include "shell.h"

/**
 * find_path - Finds command in PATH
 * @command: Command name
 *
 * Return: Full path or NULL
 */
char *find_path(char *command)
{
	char *path, *dir, *full;
	struct stat st;

	if (strchr(command, '/'))
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = getenv("PATH");
	if (!path || path[0] == '\0')
		return (NULL);

	path = strdup(path);
	if (!path)
		return (NULL);

	dir = strtok(path, ":");
	while (dir)
	{
		full = malloc(strlen(dir) + strlen(command) + 2);
		if (!full)
			break;

		sprintf(full, "%s/%s", dir, command);
		if (stat(full, &st) == 0)
		{
			free(path);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

/**
 * execute_command - Executes command if found
 * @args: Argument list
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;
	char *cmd_path;

	cmd_path = find_path(args[0]);
	if (!cmd_path)
	{
		write(STDERR_FILENO, "./shell: command not found\n", 28);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, NULL);
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		wait(&status);

	free(cmd_path);
}
