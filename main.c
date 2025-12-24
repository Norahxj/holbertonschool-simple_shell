#include "shell.h"

int last_status = 0;

#define READ_BUF_SIZE 1024

ssize_t my_getline(char **lineptr, size_t *n, int fd)
{
static char buf[READ_BUF_SIZE];
static ssize_t buf_pos = 0;
static ssize_t buf_len = 0;

size_t out_len = 0;
char *out;

if (!lineptr || !n || fd < 0)
return (-1);

if (*lineptr == NULL || *n == 0)
{
*n = 128;
*lineptr = malloc(*n);
if (!*lineptr)
return (-1);
}

out = *lineptr;

while (1)
{
if (buf_pos >= buf_len)
{
buf_len = read(fd, buf, READ_BUF_SIZE);
buf_pos = 0;

if (buf_len <= 0)
{
if (out_len == 0)
return (-1);
out[out_len] = '\0';
return ((ssize_t)out_len);
}
}

while (buf_pos < buf_len)
{
char c = buf[buf_pos++];

if (out_len + 2 > *n)
{
size_t new_n = (*n) * 2;
char *tmp = realloc(out, new_n);

if (!tmp)
return (-1);

out = tmp;
*lineptr = out;
*n = new_n;
}

out[out_len++] = c;

if (c == '\n')
{
out[out_len] = '\0';
return ((ssize_t)out_len);
}
}
}
}

int main(int ac, char **argv, char **env)
{
char *line = NULL;
size_t len = 0;
ssize_t read_bytes;
int count = 0;

(void)ac;

while (1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "($) ", 4);

read_bytes = my_getline(&line, &len, STDIN_FILENO);
if (read_bytes == -1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "\n", 1);
break;
}

count++;

/* remove trailing newline */
if (read_bytes > 0 && line[read_bytes - 1] == '\n')
line[read_bytes - 1] = '\0';

/* handle CRLF */
{
int n = _strlen(line);

if (n > 0 && line[n - 1] == '\r')
line[n - 1] = '\0';
}

/* optional: ignore empty lines */
if (line[0] == '\0')
continue;

/* builtins */
if (_strcmp(line, "exit") == 0)
{
free(line);
line = NULL;
len = 0;
handle_exit();
}

if (_strcmp(line, "env") == 0)
{
handle_env(env);
continue;
}

last_status = execute_command(line, argv[0], env, count);
}

free(line);
return (last_status);
}

