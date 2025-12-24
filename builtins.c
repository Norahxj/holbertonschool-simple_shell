#include "shell.h"

void handle_exit(void)
{
exit(last_status);
}

void handle_env(char **env)
{
int i;

for (i = 0; env && env[i]; i++)
{
write(STDOUT_FILENO, env[i], _strlen(env[i]));
write(STDOUT_FILENO, "\n", 1);
}
}
