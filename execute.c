#include "shell.h"
/**
* free_args - Frees argument array
* @args: Argument list
*/
void free_args(char **args)
{
if (args)
free(args);
}
/**
* execute_command - Executes a command
* @args: Argument list
*/
void execute_command(char **args)
{
pid_t pid;
int status;
char *full_path;

if (!args || !args[0])
return;

full_path = find_command_in_path(args[0]);
if (!full_path)
{
write(STDERR_FILENO, "./hsh: 1: ", 10);
write(STDERR_FILENO, args[0], strlen(args[0]));
write(STDERR_FILENO, ": not found\n", 12);
last_status = 127;
return;
}

pid = fork();
if (pid == 0) /* Child */
{
execve(full_path, args, environ);
perror("./hsh");
exit(127);
}
else if (pid > 0) /* Parent */
{
wait(&status);
free(full_path);
if (WIFEXITED(status))
last_status = WEXITSTATUS(status);
else
last_status = 1;
}
else
{
perror("fork");
last_status = 1;
}
}
