/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:51:19 by jiepark           #+#    #+#             */
/*   Updated: 2025/04/02 14:06:15 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

typedef struct s_mshell		t_mshell;

# define OP_SYNTAX_INVALID	-2
# define GENERAL_ERROR		1
# define SYNTAX_ERROR		2
# define CMD_INVALID		127
# define UNEXPECTED_EXIT	128

# define ERR_MSG_CMD "command not found"
# define ERR_MSG_STX "near unexpected token "
# define ERR_MSG_QOT "unclosed quote\n"
# define ERR_MSG_PAREN "unclosed parentheses\n"
# define ERR_MSG_TKN "unexpected token\n"
# define ERR_MSG_MEM "malloc error\n"
# define ERR_MSG_SYNTAX_ARG "syntax error near `"
# define ERR_MSG_SYNTAX_NO_ARG "syntax error\n"
# define ERR_CMD "Command not found"
# define ERR_STX "Syntax err near unexpected token "
# define ERR_QOT "Unclosed quote\n"
# define ERR_TKN "Unexpected token\n"
# define ERR_PAREN_STX "Unclosed parenthesis"
# define ERR_PAREN_USG "parenthesis is only allowed with && or ||"
# define ERR_EXIT_NUM "numeric argument required"
# define ERR_EXIT_ARG "too many arguments"
# define ERR_IDF "not a valid identifier"

void	err_exit(char *s, int excode);
void	err_msg(char *msg, char *name);
void	errno_msg(char *cmd, char *name);
int		err_syntax(char *input, int *i);
void	errno_exit(t_mshell *data);

#endif
