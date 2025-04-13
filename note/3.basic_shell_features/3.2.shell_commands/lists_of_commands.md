## 1. Command Lists

> **Note**: Command lists are advanced constructs often used in full-featured shells. In the 42 Minishell project, some parts are  required in the bonus part.

> **bonus part**: <br>• && and || with parenthesis for priorities.<br>
• Wildcards * should work for the current working directory.

- **Definition**:
  A command list is a sequence of one or more pipelines separated by control operators such as:
  - `;` — executes commands sequentially, regardless of the previous command's exit status.
	- **Examples**:
	```bash
	cmd1; cmd2; cmd3
	```
  - `&&` — executes the next command only if the previous command succeeded (exit status 0).
  - `||` — executes the next command only if the previous command failed (non-zero exit status).
  - `&` — executes the command asynchronously (in the background).


---
# Shell Command Operators and Special Characters

This document summarizes several shell operators and special characters. These tools are essential for controlling the flow of command execution in a shell. While understanding these concepts is useful, remember that the 42 Minishell project may only require a simplified subset of these functionalities.

---

## 1. Logical Operators: `&&` and `||`

### Logical AND (`&&`)
- **Function**: Executes the second command only if the first command succeeds (returns an exit status of 0).
- **Example**:
  ```bash
  mkdir new_folder && cd new_folder
  ```
  In this example, `cd new_folder` is executed only if `mkdir new_folder` successfully creates the directory.

### Logical OR (`||`)
- **Function**: Executes the second command only if the first command fails (returns a non-zero exit status).
- **Example**:
  ```bash
  grep "pattern" file.txt || echo "Pattern not found"
  ```
  Here, if `grep` fails to find the pattern in `file.txt`, the shell prints "Pattern not found".

### Parentheses for Priorities
- **Purpose**: Group commands to control the order of execution. Commands within parentheses are treated as a single unit.
- **Example**:
  ```bash
  (mkdir new_folder && cd new_folder) || echo "Failed to create or enter directory"
  ```
  In this grouped command, if either `mkdir` or `cd` fails, the error message is printed.

### Left Associativity
- **Concept**: When using `&&` or `||` in sequence, commands are evaluated from left to right.
- **Implication**: The return status of the entire sequence is the status of the last command executed.

## 2. Asynchronous Execution with &

- **Background Execution (`&`)**: Placing an `&` at the end of a command runs it in the background (in a subshell), allowing the shell to immediately continue with the next command.
- **Example**:
  ```bash
  sleep 10 &
  echo "This prints immediately"
  ```
  Here, `sleep 10` runs in the background while the `echo` command is executed without delay.


## 3. Wildcards (*) for the Current Working Directory

- **Wildcards**: The asterisk (`*`) matches any number of characters in filenames or directory names.
- **Usage**: When no specific path is provided, wildcards apply to the current working directory.
- **Example**:
  ```bash
  ls *.txt
  ```
  This command lists all files with a `.txt` extension in the current directory.
