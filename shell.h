#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char *read_input(void);
char **split_line(char *line);
void execute_command(char **args);
void free_args(char **args);

#endif
