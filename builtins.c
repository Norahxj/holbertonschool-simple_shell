#include "shell.h"

/**
* is_builtin - Checks if command is a built-in
* @args: Argument list
*
* Return: 1 if built-in, 0 otherwise
*/
int is_builtin(char **args)
{
if (args == NULL || args[0] == NULL)
return (0);

if (strcmp(args[0], "exit") == 0)
{
exit(EXIT_SUCCESS);
return (1);
}

return (0);
}

/**
* execute_exit - Executes the exit built-in command
*
* Return: Nothing
*/
void execute_exit(void)
{
exit(EXIT_SUCCESS);
}
