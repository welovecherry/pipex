```markdown
# Pipex

## Key Concepts Learned
- **Pipes and Redirection**: Understanding UNIX pipes and I/O redirection to connect commands and processes.
- **Process Management**: Creating and managing multiple processes using `fork()`.
- **Inter-Process Communication (IPC)**: Using pipes for communication between parent and child processes.
- **File Descriptors**: Handling file input and output efficiently through file descriptors.
- **Error Handling**: Properly handling system errors and edge cases.

## Project Overview
The **Pipex** project simulates the behavior of the shell pipeline (`|`), which allows you to redirect the output of one command to the input of another. This project is part of the 42 curriculum and serves as an introduction to **process management**, **inter-process communication**, and **file I/O** in Unix-like systems. The goal is to implement a simple pipe mechanism between two commands.

## Features
- Simulates the functionality of shell pipes (e.g., `ls | grep .c`).
- Handles file redirection (`<` and `>`) for input and output files.
- Manages multiple processes using `fork()` and `execve()`.
- Ensures proper closing of file descriptors to avoid leaks.

## How to Build
### Prerequisites
Ensure you have the following installed:
- **gcc**: The GNU Compiler Collection to compile the project.

### Build the Project
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/pipex.git
   cd pipex
   ```

2. Build the project using the `Makefile`:
   ```bash
   make
   ```

This will generate an executable named `pipex`.

## How to Run
You can run the project with the following syntax:

```bash
./pipex infile "cmd1" "cmd2" outfile
```

- **infile**: The file to be used as input.
- **cmd1**: The first command to execute.
- **cmd2**: The second command to execute, which takes the output of `cmd1` as its input.
- **outfile**: The file where the final output will be written.

### Example:
```bash
./pipex input.txt "cat" "grep pipex" output.txt
```

This command will:
- Take the content from `input.txt`.
- Run `cat` on it to output its content.
- Pass the output to `grep pipex` to filter lines containing "pipex".
- Save the result into `output.txt`.

### Bonus Features (Optional)
- **Multiple Commands**: Handle more than two commands like `cmd1 | cmd2 | cmd3 ...`.
- **Heredoc**: Implement a "here document" feature for input redirection (`<<` in shell).

## Key Files
- **pipex.c**: The main file that handles the process creation, piping, and execution of commands.
- **handle_cmd.c**: Manages the parsing and execution of commands.
- **pipex_utils.c**: Contains helper functions for file descriptor management and error handling.
- **Makefile**: Used to compile the project and clean up object files.

## Important Considerations
- **Error Handling**: Make sure to check the return values of system calls (`fork()`, `execve()`, `pipe()`, etc.) and handle errors appropriately.
- **Memory Management**: Ensure there are no memory leaks by freeing all allocated memory before exiting the program.
- **File Descriptor Management**: Properly close all file descriptors after their use to avoid resource leaks.

---

This project is part of the **42 Seoul** curriculum and focuses on understanding inter-process communication and process management in UNIX-based systems.
```
