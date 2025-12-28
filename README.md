Simple Shell Project
📖 Overview
A minimal UNIX command line interpreter written in C that replicates basic sh functionality. This project demonstrates core operating system concepts including process creation, command execution, and environment management.

✨ Features
Interactive & Non-Interactive Modes: Works with user input and piped commands

PATH Resolution: Searches for executables in PATH directories

Built-in Commands: Supports exit command

Error Handling: Displays errors matching /bin/sh format

Memory Management: No memory leaks (valgrind clean)

🛠️ Compilation
bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
🚀 Usage
Interactive Mode
bash
$ ./hsh
:) ls
file1.txt file2.txt
:) exit
$
Non-Interactive Mode
bash
$ echo "ls" | ./hsh
file1.txt file2.txt
🔄 Flowchart - How the Shell Works
┌───────────────┐
            │   Start hsh   │
            └───────┬───────┘
                    │
            ┌───────▼───────┐
            │ Display $     │
            │ (Interactive) │
            └───────┬───────┘
                    │
            ┌───────▼───────┐
            │ Read Input    │
            │ (_getline)    │
            └───────┬───────┘
                    │
        ┌───────────▼───────────┐
        │ EOF (Ctrl+D) ?         │
        └───────┬───────────────┘
                │Yes
                ▼
        ┌───────────────────┐
        │ Free memory &     │
        │ Exit shell        │
        └───────────────────┘
                ▲
                │No
        ┌───────┴───────────┐
        │ Parse input       │
        │ into arguments    │
        └───────┬───────────┘
                │
        ┌───────▼───────────┐
        │ Built-in command? │
        └───────┬───────────┘
            Yes │       No
                │
        ┌───────▼───────┐   ┌───────────────────┐
        │ Execute       │   │ Find command in    │
        │ built-in      │   │ PATH or absolute   │
        │ (exit/env)    │   │ path               │
        └───────┬───────┘   └─────────┬─────────┘
                │                     │
                │             ┌───────▼───────────┐
                │             │ Command found ?   │
                │             └───────┬───────────┘
                │                 Yes │       No
                │                     │
        ┌───────▼───────┐     ┌───────▼───────┐
        │ Update exit   │     │ Print error   │
        │ status        │     │ exit = 127    │
        └───────┬───────┘     └───────┬───────┘
                │                     │
                └───────────┬─────────┘
                            │
                    ┌───────▼───────┐
                    │ Fork process  │
                    └───────┬───────┘
                            │
                    ┌───────▼───────┐
                    │ execve()      │
                    └───────┬───────┘
                            │
                    ┌───────▼───────┐
                    │ waitpid()     │
                    │ get exit code │
                    └───────┬───────┘
                            │
                    ┌───────▼───────┐
                    │ Free memory   │
                    └───────┬───────┘
                            │
                    ┌───────▼───────┐
                    │ Loop again    │
                    └───────────────┘
📁 File Structure
text
simple_shell/
├── AUTHORS                 # Contributors list
├── README.md              # This file
├── man_1_simple_shell     # Manual page
├── shell.h                # Header file with prototypes
├── main.c                 # Entry point and main loop
├── input.c                # Input reading and parsing
├── path.c                 # PATH handling functions
├── execute.c              # Command execution logic
├── builtins.c             # Built-in commands (exit)
└── helpers.c              # Utility functions
🧠 Core Concepts Implemented
Process Management
Uses fork() to create child processes

execve() replaces process image with command

wait() suspends parent until child terminates

PATH Resolution
Checks if command contains / (absolute/relative path)

Searches directories in PATH variable

Uses access() or stat() to check file existence and permissions

Returns full path or NULL if not found

Error Handling
Matches /bin/sh error format: ./hsh: 1: command: not found

Returns exit code 127 for command not found

Uses write() for error output to avoid forbidden functions

Built-in Commands
exit: Terminates shell with exit status 0

Future: env, cd support

📝 Code Standards
Betty Style: All code follows Betty coding style guidelines

C90 Compliance: Uses -std=gnu89 flag

Memory Safety: No memory leaks, proper allocation/freeing

5 Functions per File: Modular design with limited function count

🔍 Technical Details
PID and PPID
PID: Unique process identifier (getpid())

PPID: Parent process ID (getppid())

Shell creates children with fork(), each gets new PID

Environment Manipulation
Access via extern char **environ

Custom _getenv() function (avoids forbidden getenv())

PATH parsing with strtok()

System Calls vs Functions
c
/* System Call - kernel interaction */
fork();    // Creates process
execve();  // Executes program
wait();    // Waits for child

/* Library Function - user space */
printf();  // Formatted output
strtok();  // String tokenization
malloc();  // Memory allocation
🧪 Testing
bash
# Interactive testing
./hsh

# Non-interactive testing
echo "ls" | ./hsh

# Error testing
echo "nonexistent" | ./hsh

# Memory leak check
valgrind --leak-check=full ./hsh
👥 Authors
This project is developed by Amaal Asiri and Norah Aljuhani. See AUTHORS file for complete list.

📄 License
Part of Holberton School curriculum - Educational purposes.

Project Status: Implements Simple Shell 0.3+ (PATH handling, exit built-in, command execution)
