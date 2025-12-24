#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void display_prompt(void);

char **split_line(char *line);
void free_args(char **args);

int execute_command(char **args, char *argv0, int last_status);

#endif /* SHELL_H */
