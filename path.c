#include "shell.h"
#include <sys/stat.h>

/**
* _get_env - Custom implementation to get environment variable
* @name: Name of environment variable
*
* Return: Value of variable or NULL if not found
*/
char *_get_env(const char *name)
{
int i = 0;
size_t name_len;

if (name == NULL || environ == NULL)
return (NULL);

name_len = strlen(name);

while (environ[i] != NULL)
{
if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
{
return (environ[i] + name_len + 1);
}
i++;
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

path_value = _get_env("PATH");
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
while (i > 0)
free(directories[--i]);
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
char **directories;
char *full_path = NULL;
struct stat st;
int i = 0;

if (!command || strlen(command) == 0)
return (NULL);

/* إذا كان الأمر مساراً كاملاً أو نسبياً */
if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
return (strdup(command));

directories = get_path_directories();
if (!directories)
return (NULL);

while (directories[i])
{
full_path = malloc(strlen(directories[i]) + strlen(command) + 2);
if (!full_path)
{
free_path_directories(directories);
return (NULL);
}

sprintf(full_path, "%s/%s", directories[i], command);

if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
{
free_path_directories(directories);
return (full_path);
}

free(full_path);
full_path = NULL;
i++;
}

free_path_directories(directories);
return (NULL);
}
