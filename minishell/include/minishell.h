/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:52:06 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/29 13:18:59 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include "init.h"
# include "err.h"
# include "sig_handler.h"
# include "tokenizer.h"
# include "parser.h"
# include "free_ms.h"
# include "heredoc.h"
# include "expander.h"

extern sig_atomic_t	g_exit_status;

# define MAX_INPUT_LEN 4096
# define ERR -1
# define HDC_FILE "/tmp/minishell_hd"

//maybe not needed
typedef enum e_btw_quotes
{
	NO,
	BTW_SINGLE,
	BTW_DOUBLE,
}	t_btw_quote;

typedef enum e_type
{
	TYPE_SYNTAX_INVALID,
	TYPE_TMP_WORD,
	TYPE_CMD,
	TYPE_PIPE,
	TYPE_OR,
	TYPE_AND,
	TYPE_REDIR_IN,
	TYPE_REDIR_OUT,
	TYPE_REDIR_APP,
	TYPE_REDIR_HDC,
	TYPE_PAREN_OPEN,
	TYPE_PAREN_CLOSE,
	TYPE_ENV_QUESTION,
	TYPE_ENV_VAR,
}	t_type;

typedef struct s_ast
{
	t_type			type;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_mshell
{
	t_token		*tokens;
	t_ast		*ast_root;
	t_env		*env_var;
	t_heredoc	*hdc;
	char		**envp;
	char		**path;
	int			exit_requested;
	int			dol_questn;
}	t_mshell;

/* main.c */
void	minishell(t_mshell *ms_data);

/* print_debug.c */
void	debug_print_hex(const char *str);
void	print_arr(char **str);
void	print_token(t_mshell *ms_data);
void	print_ast(t_mshell *ms_data);
char	*get_type_str(t_type type);

#endif
