# citation of bash manual

## 1.1 What is Bash?
`Bash` is the shell, or command language interpreter, for the GNU operating system. 

The name is an acronym for the `Bourne-Again SHell`, a pun on Stephen Bourne, the author of the direct ancestor of the current Unix shell sh, which appeared in the Seventh Edition Bell Labs Research version of Unix.

---

## 1.2 What is a shell?

At its base, a `shell` is simply a `macro processor` that executes commands. 

The term `macro processor` means functionality <ins>where text and symbols are expanded to create larger expressions</ins>.

A Unix shell is both a command interpreter and a programming language

> minishell is only the command interpreter part

Shells may be used interactively or non-interactively. In `interactive mode`, they accept <ins>input typed from the keyboard</ins>. When executing non-interactively, shells execute commands read from a file.

> minishell is only the interactive mode

A shell allows execution of GNU commands, both synchronously and asynchronously. 

<ins>The shell waits for synchronous commands to complete before accepting more input</ins>;

asynchronous commands continue to execute in <ins>**parallel**</ins> with the shell while it reads and executes additional commands. 

The `redirection` constructs permit fine-grained <ins>control of the input and output of those commands</ins>. 

Shells also provide a small set of `built-in` commands (`builtins`) implementing functionality impossible or inconvenient to obtain via separate utilities. 
For example, `cd`, `break`, `continue`, and     `exec` cannot be implemented outside of the shell because they directly manipulate the shell itself.

---

## 2 Definitions

### builtin
A command that is implemented internally by the shell itself, rather than by an executable program somewhere in the file system.

### control operator
A token that performs a control function. It is a newline or one of the following: ‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’.

### exit status
The value returned by a command to its caller. The value is restricted to eight bits, so the maximum value is 255.

### field
A unit of text that is the <ins>result of one of the shell expansions</ins>. After expansion, when executing a command, the resulting fields are used as the command name and arguments.

### filename
A string of characters used to identify a file.

### job
A set of processes comprising a pipeline, and any processes descended from it, that are all in the same process group.

### metacharacter
A character that, when unquoted, separates words. A metacharacter is a space, tab, newline, or one of the following characters: ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.

### operator
A control operator or a redirection operator. See Redirections, for a list of redirection operators. Operators contain at least one unquoted metacharacter.

### signal
A mechanism by which a process may be notified by the kernel of an event occurring in the system.

### token
A sequence of characters considered a single unit by the shell. It is either a word or an operator.

### word
A sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters.

---

## 3 Basic Shell Features

3.1.1 Shell Operation
The following is a brief description of the shell’s operation when it reads and executes a command. Basically, the shell does the following:

1. Reads its input from a file (see Shell Scripts), from a string supplied as an argument to the -c invocation option (see Invoking Bash), or from the user’s terminal.

2. Breaks the input into words and operators, obeying the quoting rules described in Quoting. These tokens are separated by metacharacters. Alias expansion is performed by this step (see Aliases).

3. Parses the tokens into simple and compound commands (see Shell Commands).

4. Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.

5. Performs any necessary redirections (see Redirections) and removes the redirection operators and their operands from the argument list.

6. Executes the command (see Executing Commands).

7. Optionally waits for the command to complete and collects its exit status (see Exit Status).

---

### 3.1.2.2 Single Quotes

Enclosing characters in single quotes (‘'’) preserves the literal value of each character within the quotes. A single quote may not occur between single quotes, even when preceded by a backslash.

### 3.1.2.3 Double Quotes

Enclosing characters in double quotes (‘"’) preserves the literal value of all characters within the quotes, with the exception of ‘$’, ‘`’, ‘\’,

The special parameters `*` and ‘@’ have special meaning when in double quotes (see Shell Parameter Expansion).

> If `*` in double quotes, it shouldn't be expanded

```
echo *
file1.c file2.c

echo "*"
*
```

---

> we don't handle *!* and *\\* in minishell, they're treated as normal characters.