#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

extern char **environ;
extern char *prog_name;
extern unsigned int line_number;
extern int last_status;

char *read_input(void);
char **split_line(char *line);
void free_args(char **args);

char *get_path(void);
char *find_path(char *command);
void execute_command(char **args);

void print_env(void);

#endif
