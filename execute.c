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
full_path = find_command_in_path(args[0]);
if (!full_path)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
return;
}

pid = fork();
if (pid == 0)
{
if (execve(full_path, args, environ) == -1)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
free(full_path);
exit(EXIT_FAILURE);
}
}
else if (pid > 0)
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
free(args);
}
