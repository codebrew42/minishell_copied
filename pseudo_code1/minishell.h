#ifndef MINISHELL_H
# define MINISHELL_H

/****************************** [LIBRARIES] **********************************/
# include <stdio.h>		  // Standard I/O
# include <stdlib.h>		 // Memory management
# include <unistd.h>		 // POSIX API
# include <fcntl.h>		  // File control
# include <dirent.h>		 // Directory handling
# include <sys/wait.h>	   // Process control
# include <sys/stat.h>	   // File status
# include <signal.h>		 // Signal handling
# include <errno.h>		  // Error reporting
# include <string.h>		 // String operations
# include <stdbool.h>		// Boolean types
# include <readline/readline.h>  // Readline library
# include <readline/history.h>   // Command history
# include "libft.h"		  // Custom libft functions

extern int g_exit_status;
# define MAX_INPUT_LEN 4096
# define HEREDOC_PROMPT "> "

typedef enum e_btw_quotes
{
	NO,						// no quotes started
	BTW_SINGLE				// '   btw   here   '
	BTW_DOUBLE,				// "   btw   here   "
}   t_btw_quote;

typedef enum e_token_type
{
	TOKEN_WORD,				// Regular text/command/args
	TOKEN_PIPE,				// |
	TOKEN_REDIR_IN,			// <
	TOKEN_REDIR_OUT,		// >
	TOKEN_REDIR_APPEND,		// >>
	TOKEN_REDIR_HEREDOC,	// <<
	TOKEN_ENV_VAR,			// $VAR
	TOKEN_EOF				// End of input
}   t_token_type;

typedef struct s_token
{
	t_token_type	type;		// Token type from enum
	char			*value;		// Raw string value
	struct s_token	*next;		// Next token in list
	struct s_token	*prev;		// Previous token (for backtracking)
}   t_token;

typedef struct s_ast
{
	t_token_type	type;
	char			**args;		// Command + arguments (for executables) : (ls -l | wc -l) -> args[0] = ls, args[1] = -l, args[2] = wc, args[3] = -l
	int				fd_in;
	int				fd_out;
	struct s_ast	*left;		// Left child (e.g., input source)
	struct s_ast	*right;		// Right child (e.g., next command in pipe)
}   t_ast;

typedef struct s_env
{
	char			*key;			// Variable name (e.g., "PATH")
	char			*value;			// Variable value
	struct s_env	*next;			// Next environment variable
}   t_env;

typedef struct s_shell
{
	t_token		*tokens;
	t_ast		*ast_root;			// Root of the AST
	t_env		*env;
	char		**env_array;		// Environment as char** for execve
	int			exit_requested;	// Flag for exit command
}   t_shell;



/*---------- Tokenizer ----------*/
t_token		*tokenize_input(char *input);   // Convert input string to tokens
void		free_tokens(t_token *head);	 // Cleanup token memory

/*---------- Parser ----------*/
t_ast	   *parse_tokens(t_token **tokens); // Build AST from tokens
void		free_ast(t_ast *node);		  // Recursive AST cleanup

/*---------- Environment ----------*/
t_env	   *env_init(char **envp);		 // Initialize from system env
char		*env_get(t_env *env, char *key); // Get value by key
void		env_set(t_env **env, char *key, char *value); // Set/update var
void		env_export(t_env *env);		 // Print all exported vars

/*---------- Execution ----------*/
int		 execute_ast(t_ast *node, t_shell *shell); // Core execution logic
void		handle_redirections(t_ast *node);		 // Handle I/O redirections
void		restore_stdio(int stdin_copy, int stdout_copy); // Reset file descriptors

/*---------- Builtins ----------*/
int		 builtin_cd(char **args, t_shell *shell);  // Change directory
int		 builtin_echo(char **args);				// Echo implementation
int		 builtin_export(char **args, t_shell *shell); // Export variables
int		 builtin_exit(t_shell *shell, char **args); // Exit shell

/*---------- Signal Handling ----------*/
void		setup_signals(void);			// Configure signal handlers
void		handle_sigint(int sig);		 // Ctrl+C handler

/*---------- Utilities ----------*/
char		**env_to_array(t_env *env);	 // Convert env list to char**
void		print_error(char *context, char *message); // Error reporting
int		 is_builtin(char *cmd);		  // Check if command is builtin

#endif