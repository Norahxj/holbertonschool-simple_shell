#include "shell.h"
#include <sys/stat.h>

/**
* _strdup - Duplicates a string
* @str: String to duplicate
*
* Return: Pointer to duplicated string
*/
char *_strdup(const char *str)
{
char *dup;
int i, len;

if (!str)
return (NULL);

len = strlen(str);
dup = malloc(len + 1);

if (!dup)
return (NULL);

for (i = 0; i <= len; i++)
dup[i] = str[i];

return (dup);
}

/**
* file_exists - Checks if a file exists and is executable
* @path: Path to check
*
* Return: 1 if exists and executable, 0 otherwise
*/
int file_exists(char *path)
{
struct stat st;

if (stat(path, &st) == 0)
{
if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
return (1);
}

return (0);
}
