/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:30:26 by ********          #+#    #+#             */
/*   Updated: 2025/04/01 09:56:47 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	open_file(t_cmd *cmd)
{
	if (!cmd->type_rdct[0] && !cmd->type_rdct[1])
		return (0);
	if (cmd->type_rdct[0] == TYPE_REDIR_IN || \
		cmd->type_rdct[0] == TYPE_REDIR_HDC)
		cmd->fdin = open(cmd->file_path[0], O_RDONLY);
	if (cmd->type_rdct[0] == TYPE_REDIR_HDC)
		unlink(cmd->file_path[0]);
	if (cmd->fdin < 0)
		return (ERR);
	if (cmd->type_rdct[1] == TYPE_REDIR_OUT)
		cmd->fdout = open(cmd->file_path[1], \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (cmd->type_rdct[1] == TYPE_REDIR_APP)
		cmd->fdout = open(cmd->file_path[1], \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (cmd->fdout < 0)
		return (ERR);
	return (0);
}

int	create_pipe(t_cmd *cmd)
{
	if (cmd->op != OP_PIPE)
		return (0);
	if (pipe(cmd->pipe) < 0)
		return (ERR);
	cmd->next->pipe_prev[0] = &(cmd->pipe[0]);
	cmd->next->pipe_prev[1] = &(cmd->pipe[1]);
	return (0);
}

void	close_pstream(t_cmd *cmd)
{
	if (cmd->pipe[1])
		close(cmd->pipe[1]);
	if (cmd->pipe_prev[0])
		close(*(cmd->pipe_prev[0]));
	if (cmd->fdin)
		close(cmd->fdin);
	if (cmd->fdout)
		close(cmd->fdout);
	if (!cmd->next || cmd->op == OP_AND || cmd->op == OP_OR)
		if (cmd->pipe[0])
			close(cmd->pipe[0]);
}
