#include "shell.h"

/**
 * print_env - Prints the environment variables
 */
void print_env(void)
{
	int i = 0;

	if (!environ)
		return;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
