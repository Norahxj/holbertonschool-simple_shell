#include <sys/stat.h>
#include "shell.h"

/* compare first n bytes, like strncmp */
static int _strncmp(const char *s1, const char *s2, int n)
{
int i;

for (i = 0; i < n; i++)
{
if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
return (0);
}

/* get value of PATH from env */
static char *get_path_env(char **env)
{
int i;

if (!env)
return (NULL);

for (i = 0; env[i]; i++)
{
if (_strncmp(env[i], "PATH=", 5) == 0)
return (env[i] + 5);
}
return (NULL);
}

/* build "dir/command" */
static char *join_path(const char *dir, const char *command)
{
int len_dir, len_cmd;
char *p;
int i, j;

if (!dir || !command)
return (NULL);

len_dir = _strlen(dir);
len_cmd = _strlen(command);

p = malloc(len_dir + 1 + len_cmd + 1);
if (!p)
return (NULL);

for (i = 0; i < len_dir; i++)
p[i] = dir[i];

p[i++] = '/';

for (j = 0; j < len_cmd; j++)
p[i + j] = command[j];

p[i + j] = '\0';
return (p);
}

char *find_path(char *command, char **env)
{
char *path_env;
char *path_dup;
char *dir_start;
int i;
struct stat st;

if (!command || command[0] == '\0')
return (NULL);

/* command contains '/' -> check directly */
if (_strchr(command, '/'))
{
if (stat(command, &st) == 0)
return (_strdup(command));
return (NULL);
}

path_env = get_path_env(env);
if (!path_env)
return (NULL);

path_dup = _strdup(path_env);
if (!path_dup)
return (NULL);

dir_start = path_dup;
i = 0;

while (1)
{
/* end of one PATH segment or end of string */
if (path_dup[i] == ':' || path_dup[i] == '\0')
{
char saved = path_dup[i];
char *fullpath;

path_dup[i] = '\0';

if (*dir_start != '\0')
{
fullpath = join_path(dir_start, command);
if (fullpath)
{
if (stat(fullpath, &st) == 0)
{
free(path_dup);
return (fullpath);
}
free(fullpath);
}
}

/* restore and move to next segment */
path_dup[i] = saved;

if (saved == '\0')
break;

dir_start = path_dup + i + 1;
}
i++;
}

free(path_dup);
return (NULL);
}

