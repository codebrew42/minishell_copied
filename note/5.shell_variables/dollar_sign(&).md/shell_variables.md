## to handle 
- $?
- $(VAR_MADE_BY_USER)

## don't handle
- everything else: $0, $1, $2, $*, $@, $#, $$

## 1. **Positional Parameters**
These refer to the arguments passed to a script or function.

- **`$0`**  
  - **Description:** The name of the shell script or command being executed.
  - **Example:**  
    ```bash
    echo $0
    # Output might be the name of the script or command, like "my_script.sh" or "bash"
    ```

- **`$1`, `$2`, ... `$N`**  
  - **Description:** The positional parameters that represent the arguments passed to the script. `$1` is the first argument, `$2` is the second, and so on.
  - **Example:**
    ```bash
    ./myscript.sh arg1 arg2
    echo $1  # Output: arg1
    echo $2  # Output: arg2
    ```

- **`$*`**
  - **Description:** Represents all the arguments passed to a script as a single string. Each argument is separated by a space.
  - **Example:**
    ```bash
    echo "$*"  # Output: arg1 arg2 arg3
    ```

- **`$@`**
  - **Description:** Similar to `$*`, but when quoted (`"$@"`), each argument is treated as a separate quoted string.
  - **Example:**
    ```bash
    for arg in "$@"; do
        echo "$arg"
    done
    # This prints each argument on a new line
    ```

- **`$#`**
  - **Description:** The number of arguments passed to the script.
  - **Example:**
    ```bash
    echo $#  # Output: 3 (if 3 arguments were passed)
    ```

## 2. **Special Variables**
These variables provide special functionality and context in the shell.

- **`%0`**
  - **Description:** This is not a standard shell special variable. It might be used in specific contexts or in certain shells, such as in `zsh` as a way to refer to `$0` (script name).
  
- **`%?`**
  - **Description:** This is not a standard variable in most common shells (`bash` or `zsh`), but it may be used in specific shells like `zsh` for referring to the exit status of the last command. In typical shells, `$?` is used for the exit status.
  - **Example:**
    ```bash
	#1:
    echo %?  # It might print the exit status of the last command

	#2:
    ls /nonexistent/directory
    echo $?  # Output: 2 (or another non-zero number indicating failure)
    ```

- **`%%`**
  - **Description:** In `bash` and other POSIX shells, `%%` is used to refer to the last background job.
  - **Example:**
    ```bash
    job_id=$(bg)   # Start a background job
    echo %%        # It can refer to the last background job
    ```


## 3. **Relation to the `export` Command**
The `export` command is used to set environment variables that persist for the duration of the shell session or subprocesses.

- **Example Usage:**
  ```bash
  export VAR_NAME="Hello World"
  echo $VAR_NAME  # Output: Hello World
  ```

- **Making a Variable Available to Subprocesses:**
  ```bash
  VAR_NAME="Hello"
  ./myscript.sh  # VAR_NAME is not available inside myscript.sh
  
  export VAR_NAME
  ./myscript.sh  # Now, VAR_NAME is available in the script
  ```

- **Viewing Exported Variables:**
  ```bash
  export
  ````

- **Removing an Exported Variable:**
  ```bash
  unset VAR_NAME
  ```

## 4. **42 Minishell Project and Simplified Shell Behavior**
In the `42 minishell` project, students build a simplified version of a shell that mimics `bash` behavior. Understanding special variables and `export` is essential because:

- **Command Execution:** The shell must handle positional parameters (`$1`, `$@`, etc.) correctly.
- **Exit Status Handling:** `$?` must return the correct exit code of the last executed command.
- **Environment Variables:** The shell must manage exported variables using `export`, `unset`, and `env`.
- **Job Control:** Advanced implementations may require handling `%`, `%%`, and background jobs.

For example, implementing `echo $?` correctly requires tracking the exit status of each command executed within the shell.

### Example: Handling `export` in a Minishell
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp) {
    for (int i = 0; envp[i] != NULL; i++) {
        printf("%s\n", envp[i]);
    }
    return 0;
}
```

This simple C program prints all environment variables, which is useful when implementing `export` in a minishell.

## Summary Table:

| Variable  | Description                                                                 |
|-----------|-----------------------------------------------------------------------------|
| `$0`      | Name of the script or command being executed.                              |
| `$1`, `$2`, ... `$N` | Positional parameters for the script (arguments passed to the script). |
| `$*`      | All arguments passed to the script as a single string.                     |
| `$@`      | All arguments passed to the script, each quoted separately when quoted (`"$@"`). |
| `$#`      | Number of arguments passed to the script.                                  |
| `%0`      | Likely refers to `$0` in some shells like `zsh`.                           |
| `%?`      | Exit status of the last command (commonly `$?` in most shells, `%?` in `zsh`). |
| `%%`      | Last background job (not used in standard `bash`, more common in `zsh`). |
| `$?`      | Exit status of the last command.                                           |


