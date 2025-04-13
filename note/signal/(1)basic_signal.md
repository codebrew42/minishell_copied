# Signal

## What is signal?

Signals are macros, unsigned integer, messages from user or carnel to the process.

We can see the list of signals(macros):

    man 7 signal

---

## What is the reaction of the process, if it get a signal?

If the process get a signal, there is 3 default behavior.

1. ignore the signal
2. terminate the process
3. create core dump and terminate the process

We can change the behavior in the process.

#### What is a core dump?
snapshot of the memory space.
For example, in case of segmentation fault.

---

## How to handle the signal in a program

### How to send a signal from a process to other?

We will use `kill()`. 

#### kill()

kill() is a function to send a signal to a process. Not only for killing.

ex)
```c
kill(pid, SIGKILL);
kill(pid, SIGSTOP);
kill(pid, SIGCOND);
```

### How to change the behavior, if the program get a signal?

We will use `sigaction()`.
`signal()`is not recommended in man.

#### sigaction()

sigaction() is a function to change a behavior of a process(program) for a specific signal.

We will use the `sigaction` structure for the action:

```c
struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer)(void);
};

```
#### the process
1. create sigaction structure
2. create the behavior as a function
3. set the function to the structure (sa_handler or sa_sigaction, depends on the data, which we want to give to the function)
4. set sigaction

#### example)

```c
// signal.c

#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

// 2
void    handle_tstp(int sig)
{
        printf("signal: %d\nstop not allowed.\n", sig);
}

int     main(void)
{
        pid_t   pid;
        struct sigaction sa; // 1
        sa.sa_handler = &handle_tstp; // 3
        sigaction(SIGTSTP, &sa, NULL); // 4

        pid = fork();
        if (pid)
        {
                kill(pid, SIGTSTP); // the child process will not stop, print "signal:..."
                sleep(1);
                kill(pid, SIGCONT);
        }
        else
        {
                puts("child process");
        }
}     
```

## How to block some signals while the process do the handler action? 

We can set to the sigaction structure the **mask**.

```c
struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask; // <-
    int        sa_flags;
    void     (*sa_restorer)(void);
}
```


sigset_t looks like this (but we will use setting function):

```c
#define _SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))

typedef struct
{
  unsigned long int __val[_SIGSET_NWORDS];
} __sigset_t;

```

### How to set sigset_t

We can use:

`sigemptyset()` to empty the mask.

`sigaddset()` to set a signal to the mask. 


example)

child process get `SIGTSTP` and call `handle_tstp`. While calling the parent process send `SIGTERM`, which will be blocked by the child process.

```c
// signal2.c

void    handle_tstp(int sig)
{
        printf("signal: %d\nstop not allowed.\n", sig);
        sleep(5);
}

int     main(void)
{
        pid_t                   pid;
        struct sigaction        sa;
        sigset_t                mask;

        sigemptyset(&mask);
        sigaddset(&mask, SIGTERM);

        sa.sa_handler = &handle_tstp;
        sa.sa_mask = mask;
        sigaction(SIGTSTP, &sa, NULL);

        pid = fork();
        if (pid)
        {
                kill(pid, SIGTSTP);
                sleep(1);
                kill(pid, SIGTERM);
                sleep(1);
                kill(pid, SIGCONT);
        }
        else
                puts("child process");
}                                                                                      

```


