#include "shell.h"

/**
* display_prompt - Display shell prompt
*/
void display_prompt(void)
{
write(STDOUT_FILENO, "($) ", 4);
}

