### steps
[jin]Step 1: Getting Ready  
[jin]Step 2: Tokenizer  
[jin]Step 3: Parser  
Step 4: Expander/Managing Env Var  
[kazu]Step 5: Execute  
Step 6: Signal Handler  
Step 7: utils  

### Step 1: Getting Ready  
- Read from input -> cpy "str"  
- Functions: `readline()`, `malloc`  

### Step 2: Tokenizer  
- Split input into tokens with delimiters (|<> + "", '')  
- Handle: space (' '), quote grouping ("  ", '  ') as single tokens  
- Save: each `t_token_type`  
  - WORD(cmd, arg, txt), PIPE, REDIR_IN, REDIR_OUT, REDIR_APPEND, REDIR_HEREDOC, TOKEN_ENV_VAR  
- Free(tokens): linked list  

- Functions: `ft_strchr`  
- Typedef struct: `t_token_type`  

### Step 3: Parser  
- Recursively alloc AST mem  
- Build: an AST from token list  
- Handle: pipes, red, arg grouping (remove some quotes ("", ''))  
- CP: `t_token_type` of tokens -> AST  
- Validate: syntax (bash) (e.g. no lone pipes)  
- Close open fd in REDIRECTION node  
- Return: root node of AST  
- Free(AST): node  

### Step 4: Expander/Managing Env Var  
- Order of (1)-(4): (?)  
  1. `env_init`  
     - Convert: `char**` to linked list (?)  
     - Store: PATH for quick access  
     - Handle: SHLVL, _ variables  
  2. `env_get`  
     - Search: env list for key  
     - Return: value of it or NULL (not found)  
     - Compare: case-sensitively  
  3. `expand_var`  
     - Replace: `$VAR`, `${VAR}` with env value  
     - Handle: `$?` for exit status, tilde expansion (~ -> home dir)  
     - Modify AST node arg in-place (?)  
  4. `expand_arguments`  
     - Split: after var expansion  
     - Handle: wildcards (*, ?, [ ])  

### Step 5: Execute  
1. `execute_ast`  
   - Recursively traverse AST to execute  
     - Function  
       - `strcmp(node->args[0], "ls")` -> for determining cmd  
       - `is_builtin(args[0])` -> for recognizing 'cd', 'export', ..  
   - Handle: pipes (by child processes)  
     - Function  
       ```c
       int pipe_fd[2];
       pipe(pipe_fd); // Create pipe
       // First command (writes to pipe)
       fork();
       dup2(pipe_fd[1], STDOUT_FILENO);
       execute_ast(node->left);
       // Second command (reads from pipe)
       fork();
       dup2(pipe_fd[0], STDIN_FILENO);
       execute_ast(node->right);
       ```
   - Handle: external cmd (e.g. /bin/ls)  
     - Function  
       ```c
       pid_t pid = fork();
       if (pid == 0) { // Child
           execve(cmd_path, args, env_array);
       }
       ```
   - Manage: fd (for redirection)  
   - Return: exit status of last cmd  
2. `handle_redirection`  
   - Open files: for < > >>  
   - Create tmp files: for \<< (heredoc)  
   - Modify STDIN/STDOUT: for current cmd  
3. `builtin_cd`  
   - Change: "Working dir", env var "PWD/OLDPWD"  
   - Handle: "cd -" and "cd ~"  
4. `builtin_export`  
   - Change env var  
   - Validate syntax (NAME=value)  
   - If no args, print all exported vars  

### Step 6: Signal Handler  
- Ignore: SIGQUIT (Ctrl+\)  
- Handle: SIGINT (Ctrl+C)  
- Restore default signals in child processes (?)  

### Step 7: Utils  
- `env_to_arr`: optional  
- `cleanup_shell`  


```c
/*************************** [FUNCTION PROTOTYPES] ***************************/

/*====================== LEXER ======================*/
/**
* tokenize_input(char *input)
* - Split input string into tokens (words, pipes, redirections)
* - Handle quote grouping ("...", '...') as single tokens
* - Track token types using enum e_token_type
* - Return linked list of tokens
* - Free memory with free_tokens()
*/
t_token *tokenize_input(char *input);

/**
* free_tokens(t_token *head)
* - Recursively deallocate token linked list
* - Safely handles NULL pointers
*/
void free_tokens(t_token *head);


/*====================== PARSER ======================*/
/**
* parse_tokens(t_token **tokens)
* - Build Abstract Syntax Tree (AST) from token list
* - Handle command chaining (pipes), redirections, and argument grouping
* - Validate syntax (e.g., no lone pipes)
* - Return root node of AST
*/
t_ast *parse_tokens(t_token **tokens);

/**
* free_ast(t_ast *node)
* - Recursively deallocate AST memory
* - Close open file descriptors in redirection nodes
*/
void free_ast(t_ast *node);


/*===================== EXPANDING =====================*/
/**
* expand_variables(t_ast *node, t_env *env)
* - Replace $VAR and ${VAR} with environment values
* - Handle $? for exit status
* - Process tilde expansion (~ -> home dir)
* - Modify AST node arguments in-place
*/
void expand_variables(t_ast *node, t_env *env);

/**
* expand_arguments(char **args, t_env *env)
* - Process word splitting after variable expansion
* - Handle wildcards (*, ?, [ ]) if globbing implemented
* - Return new NULL-terminated array of processed strings
*/
char **expand_arguments(char **args, t_env *env);


/*==================== EXECUTION ====================*/
/**
* execute_ast(t_ast *node, t_shell *shell)
* - Recursively traverse AST to execute commands
* - Handle pipes by creating child processes
* - Manage file descriptors for redirections
* - Return exit status of last command
*/
int execute_ast(t_ast *node, t_shell *shell);

/**
* handle_redirections(t_ast *node)
* - Open files for < > >> operators
* - Create temporary files for heredoc <<
* - Modify STDIN/STDOUT for current command
*/
void handle_redirections(t_ast *node);


/*=================== ENVIRONMENT ===================*/
/**
* env_init(char **envp)
* - Convert char** environ to linked list
* - Store PATH variable for quick access
* - Handle SHLVL and _ variables
*/
t_env *env_init(char **envp);

/**
* env_get(t_env *env, char *key)
* - Search environment list for key
* - Return value or NULL if not found
* - Case-sensitive comparison
*/
char *env_get(t_env *env, char *key);


/*==================== BUILTINS ====================*/
/**
* builtin_cd(char **args, t_shell *shell)
* - Change working directory
* - Handle "cd -" (previous dir) and "cd ~"
* - Update PWD/OLDPWD environment variables
* - Return 0 on success, 1 on error
*/
int builtin_cd(char **args, t_shell *shell);

/**
* builtin_export(char **args, t_shell *shell)
* - Add/modify environment variables
* - Validate identifier syntax (NAME=value)
* - If no args, print all exported variables
* - Return 0 on success, 1 on invalid syntax
*/
int builtin_export(char **args, t_shell *shell);


/*==================== SIGNALS =====================*/
/**
* setup_signals(void)
* - Ignore SIGQUIT (Ctrl+\)
* - Handle SIGINT (Ctrl+C) with custom handler
* - Restore default signals in child processes
*/
void setup_signals(void);


/*==================== UTILITIES ===================*/
/**
* env_to_array(t_env *env)
* - Convert environment linked list to char**
* - Format as "KEY=value" strings
* - Used for execve() compatibility
*/
char **env_to_array(t_env *env);

/**
* cleanup_shell(t_shell *shell)
* - Free tokens, AST, and environment
* - Close open file descriptors
* - Reset terminal settings
*/
void cleanup_shell(t_shell *shell);
```