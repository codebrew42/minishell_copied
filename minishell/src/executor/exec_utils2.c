/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:13:35 by ********          #+#    #+#             */
/*   Updated: 2025/04/01 11:04:00 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	set_stdinout(int from, int to)
{
	if (dup2(from, to) == ERR)
		return (ERR);
	close(from);
	return (0);
}

int	count_cmdlst(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	return (count_cmdlst(cmd->next) + 1);
}

void	moveto_parenend(t_cmd **cmd)
{
	int		i;

	i = (*cmd)->paren[0];
	while (i > 0 && *cmd)
	{
		if ((*cmd)->paren[1])
			i -= (*cmd)->paren[1];
		*cmd = (*cmd)->next;
	}
}

int	check_paren(t_ast *ast)
{
	if (check_paren_syntx(ast, 0, 0))
		return (err_msg(ERR_PAREN_STX, NULL), ERR);
	return (0);
}

/*
int	check_paren_with_op(t_ast *ast)
{
	t_type	type;

	if (!ast)
		return (0);
	if (ast->type == TYPE_PAREN_OPEN)
	{
		if (ast->left)
		{
			type = ast->left->type;
			if (type != TYPE_OR && type != TYPE_AND \
				&& type != TYPE_PAREN_OPEN)
				return (ERR);
		}
	}
	else if (ast->type == TYPE_PAREN_CLOSE)
	{
		if (ast->right)
		{
			type = ast->right->type;
			if (type != TYPE_OR && type != TYPE_AND \
				&& type != TYPE_PAREN_CLOSE)
				return (ERR);
		}
	}
	return (check_paren_with_op(ast->right));
}
*/

int	check_paren_syntx(t_ast *ast, int open, int close)
{
	if (!ast)
	{
		if (open == close)
			return (0);
		return (ERR);
	}
	if (ast->type == TYPE_PAREN_OPEN)
		open++;
	else if (ast->type == TYPE_PAREN_CLOSE)
	{
		if (open > close)
			close++;
		else
			return (ERR);
	}
	return (check_paren_syntx(ast->right, open, close));
}
