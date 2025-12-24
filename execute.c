#include "shell.h"

extern char **environ;

/**
* execute_command - Executes a command
* @args: Argument list
*/
void execute_command(char **args)
{
pid_t pid;
int status;
char *full_path = NULL;

if (!args || !args[0])
return;

/* Check if command exists before forking */
if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
{
/* Absolute or relative path */
if (!file_exists(args[0]))
{
fprintf(stderr, "./shell: 1: %s: not found\n", args[0]);
return;
}
full_path = _strdup(args[0]);
}
else
{
/* Search in PATH */
full_path = find_command_in_path(args[0]);
if (!full_path)
{
fprintf(stderr, "./shell: 1: %s: not found\n", args[0]);
return;
}
}

/* Now we know command exists, we can fork */
pid = fork();
if (pid == 0) /* Child process */
{
/* Replace current process with the command */
if (execve(full_path, args, environ) == -1)
{
/* This should not happen since we checked existence */
fprintf(stderr, "./shell: 1: %s: not found\n", args[0]);
free(full_path);
exit(EXIT_FAILURE);
}
}
else if (pid > 0) /* Parent process */
{
wait(&status);
free(full_path);
}
else
{
perror("fork");
free(full_path);
}
}

/**
* free_args - Frees argument array
* @args: Argument list
*/
void free_args(char **args)
{
if (args)
free(args);
}
