
# process

## What is a process?

a process is a program.

## How to create a new process in a program.

We can duplicaste the process with `fork()`.

`fork()` reterns `PID` of child process to the parent process, and `0` to the child process.

So we can devide the behavior like this:

```c

pid_t pid;

pid = fork();
if (pid)
{
    //do parent things.
    waitpid(pid, NULL, 0);
}
else
{
    //do child things.
}
```

## What is a zombie process?


If we use `fork()`, the parent process should **wait**.

If the child process finished, the process is still there as **zombie** until the parent process `wait` the child process.

Zombie takes resources on the mashine, so we should avoid to create zombie.

## Difference between wait functions

In minishell is allowed to use

- wait()
- waitpid()
- wait3()
- wait4()

`wait()` will wait for exit of any child process. It doesn't matter which process.

`waitpid()`
We can set the PID and wait for the process. It's also possible waiting not the exit, other status of the child process

`wait3()` and `wait4()` are similer to `wait()` and `waitpid()`,
it's useful if we need `resource usage`.

#### What is resource usage?

`resource usage` is a structure `rusage`, which we can see in the `struct_rusage.h`.

There are informations about running time, memory resorces etc.

to check the structure:

    find /usr/include -name "struct_rusage.h"

---

## How to excute a program in a process

We can excute the a program in a process with the system call `execve()`.

It's very common to use `execve()` after the `fork()`.

```c
#include <unistd.h>

int execve(const char *pathname, char *const argv[],
            char *const envp[]);

```

#### What is envp?

Environmental variable pointer.

We can get as third parameter of `main()`.

```c
int main(int ac, char **av, char **envp)
```
We can give to the `execve()` this `envp`.

example)

```c

int     main(int ac, char **av, char **envp)
{
        pid_t   n;
        char    *args[2] = {"ls", NULL};

        n = fork();
        if (n == -1)
                err_exit();
        if (!n)
        {
                if (execve("/bin/ls", args, NULL))
                        err_exit();
        }
        else
        {                                        
                write(1, "parent\n", 7);
                wait(NULL);
        }
        exit(0);
}


```