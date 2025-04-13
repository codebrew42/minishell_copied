# readline / history

---
## What is readline

With `readline()` can get a string from stdin.



```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char *readline (const char *prompt);
```

Readline and other history functions are in the `GNL readline library`.

To use the library, we need link the library by compiling:

    -lreadline

## How to use readline

We can print the prompt and get a string.
`readline()` will allocate the memory space for it.
So we have to free the line. 

```c
int main(void)
{
    char    *input;

    input = readline(">> ");
    free(input);
    //still memory leak after free...
}
```
### memory leak in readline() !
**! there is memory leaks also after free the input!**

**-> but the subject says ok. So we don't have to care about this**

### How to stop to read with ctrl + D

The user will stop to read with `CTRL + D`.
To do this, we should check the input.

```c
int     main(void)
{
        char    *input;

        while(1)
        {
                input = readline(">> ");
                if (!input) // break with ctrl + D
                        break ;                                                      
                puts(input);
                free(input); //still memory leak, but the subject says ok...
        }
        return (0);
}

```
---


## How to use history

- **add_history()**

Adding the input line to the history.

We can use in the CLI the history with `allow keys(up/down)`

- **rl_clear_history()**

Deleting **all** history.

- **rl_replace_line()**

Replacing current input  the history.

We can use for the case that user typed `ctrl + C`

In this case we replace with the empty line.

- **rl_redisplay()**

Rebuild the display with new line buffer.

We can use this function after `rl_replace_line()` by `ctrl + c`.

- **rl_on_new_line()**

Printing the new prompt.

---

### Prototypes / descriptions in the library document.

source:

https://tiswww.case.edu/php/chet/readline/readline.html#index-rl_005fredisplay

```c
void add_history (const char *string)
```
Change the time stamp associated with the  most  recent history entry to string.

```c
void rl_clear_history (void)
```
Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.

```c
 int rl_on_new_line (void)
```
Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.

```c
void rl_replace_line (const char *text, int clear_undo)
```
Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.

If clear_undo = 0, keeping the replaced history.

If clear_undo = 1, deleting the replaced history.


```c
void rl_redisplay (void)
```
Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.

---

example)

