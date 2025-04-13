## pipelines

## 1. what is a pipeline?
- sequnece/list of one or more commands separated by control operators '|' or '|&'.
	- `|` : pipe
	- `|&` : pipe with error

## 2. format
- [...] is optional, command1 is required
```bash
[time [-p]] [!] command1 [ | or |& command2 ] …

# example
ls -l | grep "file" | wc -l
```

## 3. how it works?
### case 1. just '|'
> **Note**:  this connection is performed before any redirection specified by command1** <br>
>  it is  important, when constructing a parse tree via AST
- through pipe, output of command[n] is connected to and used as input of command[n+1]

### case 2. '|&'
>  **Note**: we should decide whether to handle it or not <br>
> if we decide to, then read [Understanding `2>&1`](#1-understanding-21)
-  **`|&`** or **2>&1 |** makes sure stderr is included in the pipe.
-  command[n]'s stderr with its stdout are connected to command[n+1]'s stdin


```bash
#example
ls -l | grep "file" | wc -l 2>&1 | grep "error"
```

### comparing case 1 and case 2
#### case 1
`|` only sends **stdout** to the next command, not stderr.  
   ```bash
   some_command | grep "No such file"
   ```
- Only **stdout** of `some_command` is piped to `grep`, not stderr.  
- Even if `"No such file"` is an error message printed to stderr, `grep` won't catch it.  

#### case 2
1. **Using `2>&1 |`** (Redirect stderr to stdout before piping):  
   ```bash
   some_command 2>&1 | grep "No such file"
   ```
   - `2>&1` merges stderr (2) into stdout (1), so `grep` receives both.

2. **Using `|&` (Shortcut for `2>&1 |` in Bash 4.0+):**  
   ```bash
   some_command |& grep "No such file"
   ```
   - `|&` is equivalent to `2>&1 |` and is more concise.

## 4. timing

> **Note**: The `time` reserved word is more advanced than needed for the Minishell project – a basic understanding is sufficient.

- **Usage**: Prepending `time` to a pipeline prints timing statistics (elapsed, user, and system time) after the pipeline finishes.
- **Customization**: You can set the `TIMEFORMAT` variable to change how the timing information is displayed.

**Example**:
```bash
time ls -l | grep "pattern"
```

---

## 5. option `pipefail`

> **Note**: The `pipefail` option is an advanced feature that influences pipeline exit statuses and is not required for the Minishell project.

- **Functionality**:  
  - By default, a pipeline returns the exit status of its last command.  
  - With `pipefail` enabled, if any command fails (returns a non-zero status), the pipeline returns the exit status of the rightmost failing command. If all commands succeed, it returns 0.

**Example**:
```bash
# Enable pipefail
set -o pipefail

# In this pipeline, if 'ls' fails, the pipeline's exit status reflects that failure.
ls non_existent_dir | grep "pattern"
```

---

## 6. option `lastpipe`

> **Note**: The `lastpipe` option is an advanced shell option that allows the last command in a pipeline to run in the current shell context. This feature is not required for the Minishell project.

- **Functionality**:  
  - When enabled (and if job control is off), the final command of a pipeline executes in the current shell instead of a subshell.  
  - This can allow modifications (like variable assignments) to persist in the current shell.

**Example**:
```bash
# Enable lastpipe
shopt -s lastpipe

# The 'read' will execute in the current shell, allowing 'var' to be set and persist.
echo "hello" | read var
echo $var  # Outputs: hello
```

**Example: Without `lastpipe` Enabled**
By default (or when `lastpipe` is disabled), the final command in the pipeline runs in a subshell, so variable assignments do not persist in the parent shell.

```bash
# Ensure lastpipe is disabled (or default)
shopt -u lastpipe

echo "hello" | read var
echo $var  # Outputs nothing, as 'read' runs in a subshell.
```



<br>
<br>
---

# Additional knowledge for minishell  
## 1. Perpose of `2>&1`  
> in slack, one student says, it should work same as bash <br>
> in korean student's note, it says, it's too deep so she didn't handle it

- `2>&1` ensures that both **stdout and stderr** are processed together.
- Helps capture command failures(or errors) in pipeline by using `grep`

- If we run the command **without `2>&1`**:  
  ```sh
  ls non_existing_dir | grep "No such file"
  ```
  The output will be **empty** because `ls` sends errors to `stderr`, and `grep` only looks at `stdout`.  
- By **redirecting `stderr` to `stdout`** (`2>&1`), we ensure `grep` sees and processes the error message.

### Example 1  
```sh
ls /root 2>&1 | grep "Permission denied"

>>COMMENT
	output: ls: cannot access '/root': Permission denied
	This error message comes from `ls`, and it contains `"Permission denied"`, so `grep` displays it.
COMMENT
```
- If the user does not have permission to access `/root`, `ls` returns an error.
- `grep` filters for `"Permission denied"` messages.


### example 2  
```sh
ls non_existing_dir 2>&1 | grep "No such file"

>>COMMENT
	output: ls: cannot access 'non_existing_dir': No such file or directory
	This error message comes from `ls`, and it contains `"No such file"`, so `grep` displays it.
COMMENT
```
### 1. `ls non_existing_dir`  
- The `ls` command is used to list files in a directory.  
- Since `non_existing_dir` does not exist, `ls` produces an **error message** (sent to `stderr`).

### 2. `2>&1`  
- Redirects **stderr** (file descriptor `2`) to **stdout** (file descriptor `1`).  
- This ensures that both error messages and regular output go through the same stream.