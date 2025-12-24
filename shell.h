#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h> 

extern char **environ;
extern int last_status;

/* Function Prototypes */
char *read_input(void);
char **split_line(char *line);
void execute_command(char **args);
void free_args(char **args);
int is_builtin(char **args);
void execute_exit(void);

/* New functions for PATH handling */
char *our_getenv(const char *name);
char **get_path_directories(void);
void free_path_directories(char **directories);
char *find_command_in_path(char *command);
char *_strdup(const char *str);
int file_exists(char *path);

#endif
