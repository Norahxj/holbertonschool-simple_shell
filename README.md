# Simple Shell Project (hsh)

## Description
This project is a simple UNIX command line interpreter implemented in C as part of the Holberton School curriculum.
The shell behaves similarly to `/bin/sh`, supporting both interactive and non-interactive modes.

It reads user input, parses commands, searches executables using the `PATH` environment variable, creates child processes, and executes commands using system calls.

---

## Learning Objectives

### General
- Who designed and implemented the original UNIX operating system
- Who wrote the first version of the UNIX shell
- Who invented the B programming language (predecessor of C)
- Who is Ken Thompson
- How a shell works
- What is a PID and a PPID
- How to manipulate the environment of the current process
- Difference between a function and a system call
- How to create processes
- The three prototypes of `main`
- How the shell uses `PATH` to find programs
- How to execute another program using `execve`
- How to suspend execution until a child process terminates
- What EOF (End Of File) means

---

## Requirements

### General
- Allowed editors: `vi`, `vim`, `emacs`
- Compiled on Ubuntu 20.04 LTS
- Compilation flags:
  ```sh
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
# Simple Shell Project (hsh)

## Description
This project is a simple UNIX command line interpreter implemented in C as part of the Holberton School curriculum.
The shell behaves similarly to `/bin/sh`, supporting both interactive and non-interactive modes.

It reads user input, parses commands, searches executables using the `PATH` environment variable, creates child processes, and executes commands using system calls.

---
	•	All files end with a new line
	•	Betty coding style enforced
	•	No memory leaks
	•	Maximum 5 functions per file
	•	Header files must be include guarded
	•	System calls used only when necessary

⸻

Authorized Functions and System Calls
	•	All functions from <string.h>
	•	access, chdir, close, execve, exit, _exit
	•	fork, free, getline, getcwd, getpid
	•	isatty, kill, malloc, open, perror
	•	printf, fprintf, sprintf, putchar
	•	read, stat, lstat, fstat
	•	strtok, wait, waitpid, write

⸻

Compilation
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
⸻
Usage

Interactive Mode
$ ./hsh
($) /bin/ls
hsh main.c shell.h
($) exit

Non-Interactive Mode
$ echo "/bin/ls" | ./hsh
hsh main.c shell.h
⸻
Error Handling

The shell prints errors in the same format as /bin/sh, except that the program name matches argv[0].

Example:
./hsh: 1: qwerty: not found
⸻
Project Structure
.
├── shell.h
├── main.c
├── input.c
├── path.c
├── execute.c
└── README.md
⸻
Flowchart

The shell logic follows a structured flow:
	•	Prompt display (interactive mode)
	•	Input reading
	•	Command parsing
	•	PATH lookup
	•	Process creation and execution
	•	Exit status tracking

⸻

Authors
	•	Amaal Asiriand Norah Aljuhani
