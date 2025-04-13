/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:47:55 by ********          #+#    #+#             */
/*   Updated: 2025/04/01 10:20:51 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	init_executor(t_mshell *data, t_cmd **cmds, int **pids)
{
	int		n_cmd;
	int		i;
	t_cmd	*tmp;

	n_cmd = count_cmd(data->ast_root);
	if (!n_cmd)
		return (0);
	if (n_cmd == ERR)
		return (ERR);
	*pids = ft_calloc(n_cmd + 1, sizeof(int));
	*cmds = ft_calloc(1, sizeof(t_cmd));
	if (!*cmds)
		return (ERR);
	tmp = *cmds;
	i = n_cmd - 1;
	while (i--)
	{
		tmp->next = ft_calloc(1, sizeof(t_cmd));
		if (!tmp->next)
			return (free_cmddata(*cmds), ERR);
		tmp = tmp->next;
	}
	set_cmddata(data->ast_root, *cmds, data->hdc);
	//set_paren_status(*cmds);
	return (n_cmd);
}

void	set_cmddata(t_ast *ast, t_cmd *cmds, t_heredoc *hdc)
{
	while (ast)
	{
		if (ast->type == TYPE_CMD)
		{
			if (cmds->args)
				cmds = cmds->next;
			cmds->args = ast->args;
			cmds->bi = isbuiltin(cmds->args[0]);
		}
		else if (ast->type == TYPE_PAREN_OPEN)
			cmds->paren[0]++;
		else if (ast->type == TYPE_PAREN_CLOSE)
			cmds->paren[1]++;
		else if (ast->type == TYPE_PIPE)
			cmds->op = OP_PIPE;
		else if (ast->type == TYPE_OR || ast->type == TYPE_AND)
		{
			cmds = cmds->next;
			cmds->op = ast->type - TYPE_OR + 1;
		}
		else
			set_rdct_type(ast, cmds, ast->type, hdc);
		ast = ast->right;
	}
}

void	set_rdct_type(t_ast *ast, t_cmd *cmd, t_type type, t_heredoc *hdc)
{
	if (type == TYPE_REDIR_IN)
	{
		cmd->type_rdct[0] = type;
		cmd->file_path[0] = ast->args[0];
	}
	else if (type == TYPE_REDIR_OUT || type == TYPE_REDIR_APP)
	{
		cmd->type_rdct[1] = type;
		cmd->file_path[1] = ast->args[0];
	}
	else if (type == TYPE_REDIR_HDC)
	{
		cmd->type_rdct[0] = type;
		cmd->file_path[0] = hdc->filename;
		cmd->fdin = hdc->fd;
		hdc = hdc->next;
	}
}

void	set_paren_status(t_cmd *cmd)
{
	if (!cmd->next)
		return ;
	if (cmd->paren[0])
		cmd->next->paren[0] += cmd->paren[0] - cmd->paren[1];
	set_paren_status(cmd->next);
}
