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
* debug_print - Prints debug information
* @msg: Debug message
* @path: Path to check
*/
void debug_print(const char *msg, const char *path)
{
fprintf(stderr, "DEBUG: %s: %s\n", msg, path ? path : "(null)");
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
char **directories;
char *full_path = NULL;
struct stat st;
int i = 0;

if (!command || strlen(command) == 0)
return (NULL);

debug_print("Looking for command", command);

if (command[0] == '/' || 
(command[0] == '.' && command[1] == '/') ||
(command[0] == '.' && command[1] == '.' && command[2] == '/'))
{
debug_print("It's a relative/absolute path", command);

if (stat(command, &st) == 0 && S_ISREG(st.st_mode))
{
debug_print("File exists and is regular", command);
if (st.st_mode & S_IXUSR)
{
debug_print("File is executable", command);
return (strdup(command));
}
else
{
debug_print("File is NOT executable", command);
}
}
else
{
debug_print("File does NOT exist or is not regular", command);
}
}

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

if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
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
