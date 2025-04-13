/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:44:52 by ********          #+#    #+#             */
/*   Updated: 2025/04/01 10:46:26 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	count_cmd(t_ast *ast)
{
	int	n;

	if (!ast)
		return (ERR);
	n = 0;
	while (1)
	{
		if (ast->type == TYPE_CMD)
			n++;
		if (ast->right)
			ast = ast->right;
		else
			break ;
	}
	return (n);
}

int	op_check(t_cmd **cmd, int exit)
{
	if ((*cmd)->op == OP_OR && exit)
		return (1);
	if ((*cmd)->op == OP_AND && !exit)
		return (1);
	return (0);
}

void	free_cmdproc(t_mshell *data, t_cmd *cmd_root)
{
	free_mshell(data);
	if (cmd_root->pids)
		free(cmd_root->pids);
	free_cmddata(cmd_root);
}

void	free_cmddata(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_cmddata(cmd->next);
	if (cmd->path)
		free(cmd->path);
	free(cmd);
}

void	err_cmd(t_mshell *data, t_cmd *cmd_root, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(ERR_CMD, 2);
	free_cmdproc(data, cmd_root);
	exit(CMD_INVALID);
}
