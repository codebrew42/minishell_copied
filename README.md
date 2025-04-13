# Minishell

This Repository is a copied one from private project, written by myself and my partner.
A simple shell implementation inspired by bash.

## Description

Minishell is a simple UNIX command interpreter that replicates basic functionalities of the bash shell. It provides a command line interface where users can execute commands, manage processes, and navigate the file system.

## Features

- Command execution
- Builtin commands (cd, echo, pwd, env, export, unset, exit)
- Environment variable expansion
- Wildcards
- Redirections (>, <, >>, <<)
- Pipes
- Signal handling

## Prerequisites

- GNU Compiler Collection (GCC)
- GNU Make
- Readline library

## Installation

### On macOS

Make sure you have the readline library installed:

```bash
brew install readline
```

Build
To compile:
```bash
make
```

To recompile:
```bash
make re
```

To clean object files:
```bash
make clean
```

To remove all compiled files including the executable:
```bash
make fclean
```

## Usage

Run the minishell:
```bash
./minishell
```

You can then enter commands as you would in a regular shell:
```bash
minishell$ ls -la
minishell$ echo Hello World
minishell$ cd /path/to/directory
minishell$ exit
```


## Built-in Commands
cd [directory]: Change directory
pwd: Print working directory
echo [text]: Display text
env: Display environment variables
export [name[=value]]: Set environment variables
unset [name]: Unset environment variables
exit [status]: Exit the shell

## Project Structure
The project is organized with a clean separation between:

Command parsing and lexical analysis
AST (Abstract Syntax Tree) generation
Command execution
Built-in command implementation
Signal handling
