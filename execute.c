#include "shell.h"
#include <errno.h>

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
char *original_command = NULL;
int arg_count = 0;
char *path_env = NULL;
struct stat st;
int i = 0;

if (!args || !args[0])
return;

original_command = args[0];

fprintf(stderr, "=== DEBUG execute_command ===\n");
fprintf(stderr, "Command: '%s'\n", args[0]);

arg_count = 0;
while (args[arg_count] != NULL)
{
fprintf(stderr, "Arg[%d]: '%s'\n", arg_count, args[arg_count]);
arg_count++;
}

path_env = our_getenv("PATH");
fprintf(stderr, "Current PATH: %s\n", path_env ? path_env : "(null)");

fprintf(stderr, "Calling find_command_in_path('%s')\n", args[0]);
full_path = find_command_in_path(args[0]);
fprintf(stderr, "find_command_in_path returned: %s\n", 
full_path ? full_path : "NULL");

if (!full_path)
{
fprintf(stderr, "ERROR: Command not found\n");
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
return;
}

if (stat(full_path, &st) == 0)
{
fprintf(stderr, "File stats for '%s':\n", full_path);
fprintf(stderr, "  - Exists: YES\n");
fprintf(stderr, "  - Is regular file: %s\n", S_ISREG(st.st_mode) ? "YES" : "NO");
fprintf(stderr, "  - Executable: %s\n", (st.st_mode & S_IXUSR) ? "YES" : "NO");
fprintf(stderr, "  - Permissions: %o\n", st.st_mode & 0777);
}
else
{
fprintf(stderr, "ERROR: stat failed for '%s', errno=%d\n", full_path, errno);
}

fprintf(stderr, "Preparing to execve:\n");
fprintf(stderr, "  - Path: %s\n", full_path);
fprintf(stderr, "  - Args: ");

for (i = 0; args[i] != NULL; i++)
{
fprintf(stderr, "'%s' ", args[i]);
}
fprintf(stderr, "\n");

args[0] = full_path;

pid = fork();
if (pid == 0)
{
fprintf(stderr, "Child process: about to execve '%s'\n", full_path);

if (execve(full_path, args, environ) == -1)
{
fprintf(stderr, "ERROR: execve failed, errno=%d\n", errno);
fprintf(stderr, "./hsh: 1: %s: not found\n", original_command);
free(full_path);
exit(EXIT_FAILURE);
}
}
else if (pid > 0)
{
fprintf(stderr, "Parent process: waiting for child PID=%d\n", pid);
wait(&status);

if (WIFEXITED(status))
{
fprintf(stderr, "Child exited with status %d\n", WEXITSTATUS(status));
}
else if (WIFSIGNALED(status))
{
fprintf(stderr, "Child terminated by signal %d\n", WTERMSIG(status));
}

free(full_path);
}
else
{
fprintf(stderr, "ERROR: fork failed\n");
perror("fork");
free(full_path);
}

fprintf(stderr, "=== END DEBUG ===\n\n");
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
