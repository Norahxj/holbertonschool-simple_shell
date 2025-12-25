#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

char *read_input(void);
char **split_line(char *line);
void free_args(char **args);

char *find_path(char *command);
void execute_command(char **args);

#endif
