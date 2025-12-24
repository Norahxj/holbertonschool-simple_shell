#include "shell.h"
#include <sys/stat.h>

/**
* get_path_directories - Gets PATH environment variable
*
* Return: Array of directories in PATH
*/
char **get_path_directories(void)
{
char *path_env;
char **directories;
int i = 0, count = 0;

path_env = getenv("PATH");
if (path_env == NULL)
return (NULL);

for (i = 0; path_env[i]; i++)
if (path_env[i] == ':')
count++;
count++;

directories = malloc(sizeof(char *) * (count + 1));
if (!directories)
return (NULL);

i = 0;
directories[i] = strtok(path_env, ":");
while (directories[i] != NULL)
{
i++;
directories[i] = strtok(NULL, ":");
}

return (directories);
}

/**
* find_command_in_path - Finds command in PATH directories
* @command: Command to find
*
* Return: Full path if found, NULL otherwise
*/
char *find_command_in_path(char *command)
{
char **directories;
char *full_path = NULL;
struct stat st;
int i = 0;

if (command[0] == '/' || command[0] == '.')
return (strdup(command));

directories = get_path_directories();
if (!directories)
return (NULL);

while (directories[i])
{
full_path = malloc(strlen(directories[i]) + strlen(command) + 2);
if (!full_path)
{
free(directories);
return (NULL);
}
sprintf(full_path, "%s/%s", directories[i], command);

if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
{
free(directories);
return (full_path);
}

free(full_path);
full_path = NULL;
i++;
}

free(directories);
return (NULL);
}
