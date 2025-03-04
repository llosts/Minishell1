
# Minishell1

`minishell1` is a simple UNIX command interpreter written in C, designed as a precursor to the `42sh` project. It simulates a shell environment by interpreting basic shell commands, handling built-ins like `cd`, `setenv`, `unsetenv`, `env`, and `exit`, and executing commands in a manner similar to a traditional shell. The project aims to implement a minimalistic shell with error handling and path management.

## Features

- **Prompt**: Displays a prompt (`$>`) waiting for user input.
- **Command Execution**: Executes basic commands found in the system `PATH`.
- **Built-ins**:
  - `cd`: Changes the current directory.
  - `setenv`: Sets environment variables.
  - `unsetenv`: Removes environment variables.
  - `env`: Displays the current environment.
  - `exit`: Exits the shell.
- **Error Handling**: Displays error messages for unknown commands, invalid paths, and other errors.
- **Exit Status**: Matches the exit status of executed commands.

## Compilation

The project is compiled using the provided Makefile. It includes the following rules:
- `make`: Compiles the project.
- `make clean`: Cleans up the compiled object files.
- `make fclean`: Cleans up all generated files (including the binary).

### Compilation Instructions

To compile the project, simply run:

```bash
make
```

To clean up object files:

```bash
make clean
```

To remove all generated files:

```bash
make fclean
```

## Usage

Run the shell with:

```bash
./mysh
```

Use built-ins as follows:

```bash
$> cd /path/to/directory
$> setenv VAR value
$> unsetenv VAR
$> env
$> exit
```

## Automated Test Results

The project has been tested with various test cases. Here is the summary of the results:

100% on all the automated test.

Feel free to test my program
