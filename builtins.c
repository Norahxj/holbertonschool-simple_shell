#include "shell.h"

int is_builtin(char **args)
{
if (!args || !args[0])
return (0);

if (strcmp(args[0], "exit") == 0)
{
exit(0);
}

return (0);
}
