#include "shell.h"

/**
* is_builtin - Checks if command is a built-in
* @command: command name
*
* Return: 1 if built-in, 0 otherwise
*/
int is_builtin(char *command)
{
if (command == NULL)
return (0);

if (strcmp(command, "exit") == 0)
{
exit(EXIT_SUCCESS);
return (1);
}

return (0);
}
