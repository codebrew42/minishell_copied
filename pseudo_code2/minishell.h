/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:53:50 by ********          #+#    #+#             */
/*   Updated: 2025/02/28 17:49:02 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//added Kazu
# define ERR -1

//for tokenizer.h?
typedef enum e_btw_quotes
{
	NO,						// no quotes started
	BTW_SINGLE				// '   btw   here   '
	BTW_DOUBLE,				// "   btw   here   "
}   t_btw_quote;

typedef enum e_token_type
{
	TK_WORD,				// Regular text/command/args
	TK_PIPE,				// |
	TK_OR,
	TK_AND,
	TK_REDIR_IN,			// <
	TK_REDIR_OUT,		// >
	TK_REDIR_APP,		// >>
	TK_REDIR_HDC,	// <<
	TK_ENV_VAR,			// $VAR
	TK_EOF				// End of input
}   t_token_type;

typedef struct s_ast
{
	t_token_type	type;
	char			**args;	
	struct s_ast	*left;
	struct s_ast	*right;
}   t_ast;

typedef struct s_env
{
	char			*key;			// Variable name (e.g., "PATH")
	char			*value;			// Variable value
	struct s_env	*next;			// Next environment variable
}   t_env;

typedef struct s_mshell
{
	t_token		*tokens;
	t_ast		*ast_root;			// Root of the AST
	t_env		*env_var;
	char		**envp;		// Environment as char** for execve
	char		**path;
	int		hdc_flag;
	int			exit_requested;	// Flag for exit command
}   t_mshell;

#endif
