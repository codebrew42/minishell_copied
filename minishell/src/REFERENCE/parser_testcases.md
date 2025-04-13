# basic

## Core Data Structure
```c
typedef struct s_ast
{
	t_type          type;      // Type of node (command, pipe, redirect, etc.)
	char            **args;    // Arguments for this node (command name, file names)
	struct s_ast    *left;     // Left child node
	struct s_ast    *right;    // Right child node (next operation in sequence)
}	t_ast;
```

```c
typedef enum e_type
{
	TYPE_SYNTAX_INVALID,  // Invalid syntax 
	TYPE_TMP_WORD,        // Temporary word (during parsing)
	TYPE_CMD,             // Command node
	TYPE_PIPE,            // Pipe operator (|)
	TYPE_OR,              // Logical OR (||)
	TYPE_AND,             // Logical AND (&&)
	TYPE_REDIR_IN,        // Input redirection (<)
	TYPE_REDIR_OUT,       // Output redirection (>)
	TYPE_REDIR_APP,       // Append redirection (>>)
	TYPE_REDIR_HDC,       // Heredoc (<<)
	TYPE_ENV_QUESTION,    // $? (exit status)
	TYPE_ENV_VAR,         // Environment variable
}	t_type;
```

## Example AST Structures

which type has no args? TYPE_AND, TYPE_OR, TYPE

### 0. add
```
cm1 | cm2 | cm3
```

```total 5 nodes
TYPE_CMD (cm1)
  args: ["cm1"]
  right: TYPE_PIPE
           right: TYPE_CMD (cm2)
                    args: ["cm2"]
                    right: TYPE_PIPE
                             right: TYPE_CMD (cm3)
                                      args: ["cm3"]
```

``` 
cm1 > file1 < file2
```

```total 3 nodes
TYPE_CMD (cm1)
  args: ["cm1"]
  right: TYPE_REDIR_OUT
           args: ["file1"]
           right: TYPE_REDIR_IN
                    args: ["file2"]
```

### 1. Simple Command with Pipes
```
ls -la | grep "pattern" | wc -l
```

```5 nodes
TYPE_CMD (ls)
  args: ["ls", "-la"]
  right: TYPE_PIPE
           right: TYPE_CMD 
                    args: ["grep", "pattern"]
                    right: TYPE_PIPE
                             right: TYPE_CMD (wc)
                                      args: ["wc", "-l"]
```

### 2. Command with Redirections
```
grep "pattern" < input.txt > results.txt > errors.log
```

```5 nodes
TYPE_CMD
  args: ["grep", "pattern"]
  right: TYPE_REDIR_IN
           args: ["input.txt"]
           right: TYPE_REDIR_OUT
                    args: ["results.txt"]
                    right: TYPE_REDIR_OUT
                             args: ["errors.log"]
```

### 3. Logical Operators
```
grep "pattern" file.txt && echo "Found" || echo "Not found"
```

```5 nodes
TYPE_CMD 
  args: ["grep", "pattern", "file.txt"]
  right: TYPE_AND
           right: TYPE_CMD
                    args: ["echo", "Found"]
                    right: TYPE_OR
                             right: TYPE_CMD
                                      args: ["echo", "Not found"]
```

### 4. Heredoc Redirection
```
cat << EOF > output.txt
```

```3 nodes
TYPE_CMD 
  args: ["cat"]
  right: TYPE_REDIR_HDC
           args: ["EOF"]
           right: TYPE_REDIR_OUT
                    args: ["output.txt"]
```

### 5. Parentheses Grouping
```
(echo "hello" && ls) || echo "failed"
```

```total 7 nodes
TYPE_PAREN_OPEN
  right: TYPE_CMD 
           args: ["echo", "hello"]
           right: TYPE_AND
                    right: TYPE_CMD 
                             args: ["ls"]
							 right: TYPE_PAREN_CLOSE
	                             right: TYPE_OR
                                      right: TYPE_CMD
                                               args: ["echo", "failed"]
```



# more test cases
## 1.
echo "Double quotes: \$variable \"quoted\" \\backslash \nnewline \a\b\c"
echo Unquoted: \$variable \"quoted\" \\backslash \a\b\c \* \( \)
echo "Double quoted: \z"
echo Unquoted: \z

## 2.
echo "This contains 'single quotes' inside double quotes"
echo "quoted" vs "\\"quoted\\""
echo "The date is \`date\`"
echo "$USER"
echo "\$USER vs $USER"
echo "    spaced    text    " vs     unquoted    spaces
echo 'Can\'t escape this'
echo "double"'single'"mixed"
echo "testing line continuation" \`
echo "$USER is user on $HOSTNAME"
echo Hello; World
echo "piped | content" | wc -c
cat << "EOF" | grep "pattern"
echo "line1\nline2"
echo "Unmatched quote`

## 3

echo "Double quotes: \$variable \"quoted\" \\backslash \nnewline \a\b\c"
echo Unquoted: \$variable \"quoted\" \\backslash \a\b\c \* \( \)
echo "Double quoted: \z"
echo Unquoted: \z
echo "This contains 'single quotes' inside double quotes"
echo "quoted" vs "\\"quoted\\""
echo "The date is \`date\`"
echo X="$USER"; echo "$X"
echo "\$USER vs $USER"
echo "    spaced    text    " vs     unquoted    spaces
echo 'Can\'t escape this'
echo "double"'single'"mixed"
echo "testing line continuation" \`
echo "$USER is user on $HOSTNAME"
echo Hello; World
echo "piped | content" | wc -c
cat << "EOF" | grep "pattern"
echo "line1\nline2"
echo "*\"*"`
echo '$USER' "$USER" \$USER
echo "my path is $PATH"
ls -la > "file with spaces.txt"
echo $'special\nchars'
echo $"translated $USER"
echo \`ls\` vs $(ls)
echo $((5 + 3)) \$((5 + 3))
IFS=":"; echo "$PATH"
echo "\\" '\\' \\
echo "a\"b\"c"
export X="test"; echo ${X:-default}
