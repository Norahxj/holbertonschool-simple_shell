# Holberton School - Simple Shell

## Description
**Simple Shell** is a UNIX command interpreter written in C that replicates the basic functionality of `/bin/sh`.  
It executes commands in both interactive and non-interactive modes, handles built-in commands, PATH searching, and manages exit statuses properly.

---

## Features
- ✅ Display a prompt and wait for user input
- ✅ Execute commands with absolute paths (e.g., `/bin/ls`)
- ✅ Execute commands using the PATH environment variable (e.g., `ls`)
- ✅ Handle command lines with arguments (e.g., `ls -l /tmp`)
- ✅ Implement custom PATH searching without `getenv`
- ✅ Handle the `exit` built-in command with proper exit status
- ✅ Handle the `env` built-in command
- ✅ Handle end-of-file condition (Ctrl+D)
- ✅ Proper exit status handling (0, 127, etc.)
- ✅ No memory leaks (Valgrind clean)
- ✅ No unnecessary `fork` calls if command doesn't exist

---

---

## Key Functions

| File           | Function                | Description                                                    |
|----------------|------------------------|----------------------------------------------------------------|
| main.c         | main()                 | Entry point, manages shell loop and exit status               |
| shell.c        | display_prompt()       | Displays shell prompt `$`                                      |
| shell.c        | read_line()            | Reads input from user using custom `_getline`                 |
| shell.c        | parse_line()           | Parses input into array of arguments                          |
| shell.c        | free_array()           | Frees allocated memory for argument array                     |
| find_path.c    | get_path_env()         | Gets PATH from `environ` without `getenv`                     |
| find_path.c    | find_path()            | Searches for command in PATH directories                      |
| run_command.c  | fork_and_execute()     | Forks and executes command with proper exit status            |
| run_command.c  | execute_command()      | Main execution logic, returns correct exit codes              |
| builtin.c      | handle_exit()          | Handles `exit` command with last exit status                  |
| builtin.c      | handle_env()           | Prints environment variables                                   |
| builtin.c      | is_builtin()           | Checks and executes built-in commands                          |

---

## Built-in Commands

| Command | Description                           | Usage  |
|---------|---------------------------------------|--------|
| exit    | Exit the shell with last command exit | exit   |
| env     | Print all environment variables       | env    |

---

## Technical Details

**Memory Management**
- All allocated memory is properly freed
- No memory leaks (verified with Valgrind)
- `exit` command frees all resources before exiting

**Process Management**
- Uses `fork()` to create child processes
- Uses `execve()` to execute commands
- Uses `waitpid()` to wait for child and get exit status
- Uses `WIFEXITED()` and `WEXITSTATUS()` macros

**PATH Handling**
- Custom `get_path_env()` replaces forbidden `getenv()`
- Searches through `environ` array directly
- Handles empty PATH correctly
- Returns `NULL` for commands not found in PATH

---

## Project Information

- **Language:** C  
- **C Standard:** gnu89  
- **License:** Educational purposes (Holberton School)  
- **Total Functions:** 12 functions across 5 files (max 4 per file)

## Project Structure

| File          | Description                          | Functions                                         |
| ------------- | ------------------------------------ | ------------------------------------------------- |
| main.h        | Header file with function prototypes | N/A                                               |
| main.c        | Main entry point and shell loop      | main()                                            |
| shell.c       | Core shell functions                 | display_prompt, read_line, parse_line, free_array |
| find_path.c   | Custom PATH searching without getenv | get_path_env, find_path                           |
| run_command.c | Command execution and process mgmt   | fork_and_execute, execute_command                 |
| builtin.c     | Built-in commands implementation     | handle_exit, handle_env, is_builtin               |
| README.md     | Project documentation                | N/A                                               |
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

Amaal Asiri
Norah Aljuhani
