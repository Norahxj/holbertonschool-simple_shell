#include "shell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

/**
 * get_path_from_env - Retrieves PATH manually from environment
 * @env: environment variables array
 *
 * Return: PATH string or default "/bin:/usr/bin"
 */
static char *get_path_from_env(char **env)
{
	int i = 0;

	if (!env)
		return ("/bin:/usr/bin");

	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}

	return ("/bin:/usr/bin");
}

/**
 * find_path - Finds command in PATH
 * @command: Command name
 *
 * Return: Full path or NULL
 */
char *find_path(char *command)
{
	char *path, *dir, *full, *path_copy;
	struct stat st;

	if (strchr(command, '/'))
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = get_path_from_env(environ);
	if (!path || path[0] == '\0')
		path = "/bin:/usr/bin";

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full = malloc(strlen(dir) + strlen(command) + 2);
		if (!full)
			break;

		sprintf(full, "%s/%s", dir, command);
		if (stat(full, &st) == 0)
		{
			free(path_copy);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
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

	if (!args || !args[0])
		return;

	cmd_path = find_path(args[0]);
	if (!cmd_path)
	{
		write(STDERR_FILENO, "./shell: command not found\n", 28);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		wait(&status);

	free(cmd_path);
}
