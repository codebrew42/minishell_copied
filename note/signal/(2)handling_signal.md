# Handling Signals in Minishell

## 1. Understanding Signals in Minishell

### script control for minishell
- control+c : SIGINT
- control+d : EOF
- control+\ : SIGQUIT

### What Are Signals?
Signals are notifications sent to a process to notify it of events like keyboard interrupts (Ctrl+C) or quit signals (Ctrl+\). Minishell must handle these signals properly to behave like a real shell.

### Important Signals
- **SIGINT (Ctrl+C)**: Interrupts a running process.
- **SIGQUIT (Ctrl+\)**: Quits a process and generates a core dump.
- **EOF (Ctrl+D)**: Indicates the end of input (not technically a signal but behaves like one in a shell).

## 2. How Minishell Handles Signals

### 1. `define_signal(void)`
This function is responsible for setting up signal handling in Minishell. It assigns specific behavior to different signals.

### 2. `signal_interrupt(int signbr)`
This function is triggered when a signal is received. It decides what to do based on the type of signal.

### 3. `handle_signal(int signbr)`
This function processes signals when received. The flow is:

1. Call `waitpid()` to check if a child process exists.
2. If the received signal is **SIGINT (Ctrl+C)**:
   - If no child process has changed status (`pid == -1`), clear the input line and redisplay the prompt.
   - Otherwise, handle the signal in the child process.
3. If the received signal is **SIGQUIT (Ctrl+\\)**:
   - If no child process has changed status (`pid == -1`), ignore it.
   - Otherwise, display the quit message.

#### Behavior When Receiving Signals
- **SIGINT (Ctrl+C)**:
  - Writes a new line (`\n`).
  - If no child process has changed status (`pid == -1`) or if the current input is incomplete:
    - Clear the input line and redisplay the prompt.
    - If not, just clear the input line.

#### Global Variable `g_exit_code`
- `g_exit_code = 1` is set when SIGINT is received.
- It helps track if an interrupt occurred.

#### function `waitpid(-1, &status, WNOHANG)`

- `waitpid(-1, &status, WNOHANG)` is used to check if a child process has exited.
- `WNOHANG` makes `waitpid` return immediately if no child has exited.
- `status` is required but may not always be used.
- If `pid == -1`, no child process has exited.

### 4. `handler_heredoc(int signbr)`
- If a signal is received in `heredoc` mode:
  - Update `g_exit_code`.
  - Write a new line.
  - Close the input.

## 5. Order of Execution in Minishell
The execution order affects signal handling. The main steps are:

1. **Redirection Processing**
2. **Pipe Processing** (Handles whether output goes into a pipe)
3. **Forking (Multiprocessing)**
4. **Execution** (Decides whether to run built-in functions or use `execve`)
   - Initially, signals were handled per pipe, but later all processes were executed first, and then `wait` was called.
5. **Exit Handling** (For built-in functions, exit is managed separately; for `execve`, the process terminates itself.)
6. **Shell Re-input Stage** (Handles memory cleanup and prepares for new input.)

### handle redirection, and then pipe
- why? handling redirection ensures input/output streams are set up before data is passed through pipes
	- redirection changes where input comes from and where ouput goes
- So, once redirection is set, pipes can connect the output of one process to the input of another
- Again, any redirection(sending output to a file) -> and then, pipe the data to another process

## 6. Implementing Signal Handling

### Signal Interception
We need to handle:
- **Ctrl+C (SIGINT)**
- **Ctrl+\ (SIGQUIT)**
- **Ctrl+D (EOF, handled separately in the prompt)**

```c
#define SHE 0
#define DFL 1
#define IGN 2

void signal_handler(int signo)
{
    if (signo == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    if (signo == SIGQUIT)
    {
        rl_on_new_line();
        rl_redisplay();
    }
}
```

### Setting Signal Handling Modes
```c
void set_signal(int sig_int, int sig_quit)
{
    if (sig_int == IGN)
        signal(SIGINT, SIG_IGN);
    if (sig_int == DFL)
        signal(SIGINT, SIG_DFL);
    if (sig_int == SHE)
        signal(SIGINT, signal_handler);
    if (sig_quit == IGN)
        signal(SIGQUIT, SIG_IGN);
    if (sig_quit == DFL)
        signal(SIGQUIT, SIG_DFL);
    if (sig_quit == SHE)
        signal(SIGQUIT, signal_handler);
}
```

### Applying Signal Handling
1. When executing a command:
   - Before `fork()`, set signals to default (`DFL`).
   - After `fork()`, make the parent ignore signals (`IGN`).
2. After execution, reset signals for the next prompt.

```c
set_signal(DFL, DFL);
pid = fork();
if (pid == 0)
{
    redirect(cmd);
    close_unused_fd(cmd, pid);
    exit_code = execute_cmd(cmd, env_head);
    exit(exit_code);
}
else
{
    close_unused_fd(cmd, pid);
    set_signal(IGN, IGN);
}
```

### Handling `SIGINT` and `SIGQUIT` in Child Processes
```c
void wait_child(void)
{
    int status;
    int signo;
    int i = 0;
    
    while (wait(&status) != -1)
    {
        if (WIFSIGNALED(status))
        {
            signo = WTERMSIG(status);
            if (signo == SIGINT && i++ == 0)
                ft_putstr_fd("^C\n", STDERR_FILENO);
            else if (signo == SIGQUIT && i++ == 0)
                ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
            g_exit_code = 128 + signo;
        }
        else
            g_exit_code = WEXITSTATUS(status);
    }
}
```

### Explanation
- `wait(&status)`: Waits for child processes to finish.
- `WIFSIGNALED(status)`: Checks if a child process was terminated by a signal.
- `WTERMSIG(status)`: Gets the signal number that caused termination.
- Prevents multiple `^C` or `^\Quit: 3` messages when terminating multiple processes.

## 7. Conclusion
- Proper signal handling makes Minishell behave like a real shell.
- Signals must be managed differently for parent and child processes.
- `waitpid()` and global variables help track process states.
- Handling signals correctly ensures smooth execution and prompt redisplay.

By implementing these signal handlers, Minishell can respond correctly to user inputs like Ctrl+C and Ctrl+\ while executing commands efficiently.

