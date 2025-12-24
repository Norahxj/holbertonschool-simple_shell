#include "shell.h"

int execute_command(char *line, char *prog, char **env, int count)
{
char **argv;
char *path;
pid_t pid;
int status;

argv = split_line(line);
if (!argv || !argv[0])
{
free_argv(argv);
return (0);
}

path = find_path(argv[0], env);
if (!path)
{
print_error(prog, argv[0], count);
free_argv(argv);
return (127);
}

pid = fork();
if (pid == -1)
{
free(path);
free_argv(argv);
return (1);
}

if (pid == 0)
{
execve(path, argv, env);
print_error(prog, argv[0], count);
_exit(127);
}

waitpid(pid, &status, 0);
free(path);
free_argv(argv);

if (WIFEXITED(status))
return (WEXITSTATUS(status));

return (1);
}

