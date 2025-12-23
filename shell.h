#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * read_line - Reads a line of input from the user
 * Return: pointer to the input string (must be freed by caller)
 */
char *read_line(void);

/*
 * execute_command - Executes a single command using fork and execve
 * @line: command to execute
 * Return: void
 */
void execute_command(char *line);

#endif
