#include "shell.h"
#include <sys/stat.h>
#include <errno.h>

extern char **environ;

/**
* our_getenv - Gets environment variable value
* @name: Variable name
*
* Return: Value or NULL
*/
char *our_getenv(const char *name)
{
int i = 0;
size_t name_len;

if (name == NULL || environ == NULL)
return (NULL);

name_len = strlen(name);

for (i = 0; environ[i] != NULL; i++)
{
if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
{
return (environ[i] + name_len + 1);
}
}

return (NULL);
}

/**
* get_path_directories - Gets PATH directories safely
*
* Return: Array of directories (must be freed) or NULL
*/
char **get_path_directories(void)
{
char *path_value;
char *path_copy;
char **directories;
int i = 0, count = 0;
char *token;

path_value = our_getenv("PATH");
if (path_value == NULL || strlen(path_value) == 0)
return (NULL);

path_copy = strdup(path_value);
if (path_copy == NULL)
return (NULL);

for (i = 0; path_copy[i]; i++)
if (path_copy[i] == ':')
count++;
count++;

directories = malloc(sizeof(char *) * (count + 1));
if (!directories)
{
free(path_copy);
return (NULL);
}

i = 0;
token = strtok(path_copy, ":");
while (token)
{
directories[i] = strdup(token);
if (!directories[i])
{
int j;
for (j = 0; j < i; j++)
free(directories[j]);
free(directories);
free(path_copy);
return (NULL);
}
i++;
token = strtok(NULL, ":");
}
directories[i] = NULL;

free(path_copy);
return (directories);
}

/**
* free_path_directories - Frees path directories array
* @directories: Array to free
*/
void free_path_directories(char **directories)
{
int i = 0;

if (!directories)
return;

while (directories[i])
{
free(directories[i]);
i++;
}
free(directories);
}

/**
* find_command_in_path - Finds command in PATH
* @command: Command to find
*
* Return: Full path or NULL
*/
char *find_command_in_path(char *command)
{
char **dirs;
char *full;
int i;
struct stat st;

if (!command)
return (NULL);

if (command[0] == '/' || command[0] == '.')
{
if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
return (_strdup(command));
return (NULL);
}

dirs = get_path_directories();
if (!dirs)
return (NULL);

for (i = 0; dirs[i]; i++)
{
full = malloc(strlen(dirs[i]) + strlen(command) + 2);
if (!full)
break;

strcpy(full, dirs[i]);
strcat(full, "/");
strcat(full, command);

if (stat(full, &st) == 0 && (st.st_mode & S_IXUSR))
{
free_path_directories(dirs);
return (full);
}
free(full);
}

free_path_directories(dirs);
return (NULL);
}
