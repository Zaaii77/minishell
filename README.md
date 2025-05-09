# Minishell

`minishell` is a minimalistic shell implementation in C, inspired by Bash. It supports basic shell functionalities, including command execution, environment variable management, and redirections.

## Features
- Command execution with arguments.
- Built-in commands: `cd`, `echo`, `pwd`, `export`, `unset`, `exit`.
- Environment variable handling.
- Input/output redirections and pipes.
- Support for `heredoc`.
- Signal handling for interactive mode.

## Requirements
- A Unix-like operating system.
- `readline` library installed on your system.

## How to Build and Run
1. Clone the repository:
   ```bash
   git clone git@github.com:Zaaii77/minishell.git
   cd minishell
   ```

2. Compile the project:
   ```bash
   make
   ```

3. Run the shell:
   ```bash
   ./minishell
   ```

## Built-in Commands
- `cd [directory]`: Change the current directory.
- `echo <flags> [args]`: Print arguments to the standard output.
- `pwd`: Print the current working directory.
- `export [name] <=value>`: Set or update environment variables.
- `unset [name]`: Remove environment variables.
- `exit [status]`: Exit the shell with an optional status code.

## Redirections and Pipes
- `>`: Redirect output to a file.
- `>>`: Append output to a file.
- `<`: Redirect input from a file.
- `<<`: Use heredoc to provide input until a delimiter is reached.
- `|`: Pipe the output of one command to the input of another.

## Signals
- `Ctrl+C`: Interrupt the current process.
- `Ctrl+D`: Exit the shell.
- `Ctrl+\`: Quit the current process. (Only in externals functions)

## Example Usage
```bash
minishell$ echo "Hello, World!"
Hello, World!

minishell$ export MY_VAR=42
minisehll$ echo $MY_VAR
42

minishell$ ls | grep minishell > output.txt
```

## Notes
- The project is built using the `libft` library for utility functions.
- It adheres to the 42 coding standards.

## License
This project is licensed under the MIT License.
