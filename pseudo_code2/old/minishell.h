/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:53:50 by ********          #+#    #+#             */
/*   Updated: 2025/02/27 14:54:18 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include "libft.h"

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_RED_IN,
	TK_RED_OUT,
	TK_RED_APP,
	TK_RED_HEDC,
	TK_ENVAR,
	TK_EOF	

}   t_token_type;

typedef struct s_token
{
	char	*name;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
	char		**args;
	t_token		*types;
	struct s_ast 	*left;
	struct s_ast 	*right;
}	t_ast;

typedef struct	s_data
{
	t_token	*tokens; //into parser structure?
	t_ast	*ast;
	t_ast	*root; //for free
	char	**ev;
	char	**envp;
	char	**path;
}	t_data;
