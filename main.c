#include "shell.h"

/**
* main - Simple UNIX command line interpreter
*
* Return: Always 0
*/
int last_status = 0;

int main(void)
{
char *line;
char **args;
int interactive = isatty(STDIN_FILENO);

while (1)
{
if (interactive)
write(STDOUT_FILENO, ":) ", 3);

line = read_input();
if (!line)
{
if (interactive)
write(STDOUT_FILENO, "\n", 1);
break;
}

args = split_line(line);
if (args && args[0])
{
if (!is_builtin(args))
{
execute_command(args);
}
}

free_args(args);
free(line);
}

return (0);
}
