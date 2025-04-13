## 1. simple commands in minishell
### what is a simple command?
- single sequence of words(tokens) that includes: command name(executable or builtin) + arguments(optional) + redirections(optional)

	```bash
	ls -l /home/user
	```

- **command name(executable)**: `ls`
- **arguments**: `-l`, `/home/user`
- **redirections**: `<`, `>`

### control operators in simple commands
- simple commands are terminated by a control operator
	- `;` : execute the next command in the next line (sequential execution)
	- `|` : pipe to the next command
	- `&` : execute the command in the background
	- `&&` : execute the next command only if the previous command succeeds
	- `||` : execute the next command only if the previous command fails

	```bash
	echo "hi" && ls
	```
	- echo runs -> if success(=exit status is 0), ls runs
	- echo runs -> if failure(=exit status is not 0), ls does not run
## 2. execution of simple commands
1. **parsing**
- split the input into tokens (command, arguments, redirections)
- create a command node in the abstract syntax tree (AST)

2. **forking and executing**
- (1). if it's a **these five built-ins**, execute it directly (e.g., `cd`, `pwd`, `export`, `unset`, `exit`)
- (2). if it's an **external executable** or **two built-ins(=`echo`, `env`)**, create a child process using `fork()`
	- (2-1) fork() creates a child process(a duplicate process)
	- (2-2) (in the child process) it searches for the executable file in the `PATH` environment variable
	- (2-3) if found, the child process replaces itself with the executable file
		- (= the shell uses one of the **exec family of functions** to load and run the program)
		- how? using `execve()`, `execvp()`, `execvpe()`
	- (2-4) if not found, the child process is terminated with a message

3. **waiting**
- wait for the child process to finish
- get the exit status of the child process

4. **handling return status**
- shell retrieves the command's return status using `waitpid()`
	- if the process exits normally, the return status is the exit status of the process
	- if terminated by a signal, the return status is `128 + signal number`
	(e.g., SIGKILL (9) -> exit code 137)
- the return status of a command is stored in the global variable `g_status`

- example
```bash
#1
echo Hello #return value is 0
echo $? #return value is 0

#
cat
^C #terminate with SIGINT

echo $? #return value is 130 (128 + 2)

```


