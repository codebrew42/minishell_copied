
## redirections

### 0. what **redirections** can do?
- 1. allows commands' file handles to be duplicated, opened, closed, made to refer to dfferent files
- 2. changes files which commands reads from and write to
- 3. modifies file handles in the current shell.
	- **note:** file handles  
	stdin: File handle 0, used for reading input.  
	stdout: File handle 1, used for writing output.  
	stderr: File handle 2, used for writing error messages.  

### **1. Processed Left to Right**  
- Redirections are processed in the order they appear, from left to right.  
- This means that earlier redirections affect later ones, which can lead to unexpected behavior if not carefully managed.  

### **2. Redirections with File Descriptors (FD)**  

#### **2-1. Used with File Descriptors NUMBERS**  
> **skip!** 
- Redirections can be explicitly preceded by a file descriptor (e.g., `2> file.txt`, `3>&1`).  
- If no FD is provided, it defaults to **stdin (0)** for `<` and **stdout (1)** for `>`.  

#### **2-2. Used with `{varname}`**  
> **skip! do not need to handle!** 
- A redirection can also be preceded by `{varname}`, which allows dynamic FD management.  
- **Case 1: Redirections except `>&-` or `<&-`**  
  - The shell allocates a file descriptor greater than 10 and assigns it to `{varname}`.  
  - Example:  
    ```bash
    exec {myfd}>output.txt
    echo "Hello" >&$myfd
    exec {myfd}>&-
    ```  
- **Case 2: `>&-` or `<&-`**  
  - The value of `{varname}` determines the FD to be closed.  
  - Example:  
    ```bash
    exec {myfd}>output.txt
    exec {myfd}>&-  # Closes the allocated FD
    ```  

### **3. Importance of Redirection Order**  
- The order in which redirections are written affects the final result.  
- Example:  
  ```bash
  ls > dirlist 2>&1  # Redirects both stdout and stderr to 'dirlist'
  ls 2>&1 > dirlist  # Only stdout is redirected, stderr still points to the original stdout
  ```  

---
ls -l
/bin/ls -l
## **Special Redirection Files in Bash**  


- `/dev/fd/N` →file descriptor `N` is duplicated. (N = valid integer fd)  
- `/dev/stdin` → Standard input (fd `0` is duplicated).  
- `/dev/stdout` → Standard output (fd `1` duplicated).  
- `/dev/stderr` → Standard error (fd `2` duplicated).  
- `/dev/tcp/host/port` → Opens a TCP socket.  
	- If host is a valid hostname or Internet address, and port is an integer port number or service name, Bash attempts to open the corresponding TCP socket.
- `/dev/udp/host/port` → Opens a UDP socket.  
	- If host is a valid hostname or Internet address, and port is an integer port number or service name, Bash attempts to open the corresponding UDP socket.
- **Note:** If the OS doesn’t support these, Bash emulates them.  

### **Failure Cases**  
- If a file cannot be opened or created, redirection fails.  
- Using FD numbers greater than `9` can be risky as the shell may use them internally.  

---

## **Additional Notes for Minishell Implementation**  
- **Parsing redirections**:  
  - Handle redirections in the correct left-to-right order.  
  - Ensure proper FD allocation when `{varname}` is used.  
- **Handling special cases**:  
  - Implement error handling for invalid file descriptors or permissions.  
  - Support special redirection files if necessary.  
- **File descriptor limits**:  
  - Be mindful of system-imposed FD limits.  
  - Implement proper closing mechanisms to prevent leaks.  

### etc
- < : input
  - Redirects input from a file to a command.
  - Example: `pbcopy < ~/.ssh/id_ed25519.pub` copies the content of the file to the clipboard.
```bash
#copy to clipboard
pbcopy < ~/.ssh/id_ed25519.pub 
pbcopy < file.txt
```

- \> : output
  - Redirects output from a command to a file, overwriting the file if it exists.
  - Example: `echo "Hello" > output.txt` writes "Hello" to `output.txt`, replacing any existing content.


- \>> : same as >, but append
- << : here document
	- Takes user input, including line breaks, until the specified string on the right side of the operator (e.g., EOF) is encountered.
	- sends all the read input except the delimiter to the left program as standard input.
```bash
cat << EOF
> hello
> EOF

--result--
hello
```