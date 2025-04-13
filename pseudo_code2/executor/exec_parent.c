/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:30:26 by ********          #+#    #+#             */
/*   Updated: 2025/03/01 19:35:10 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#incldue "minishell.h"

void	create_cmdproc(t_data *data, t_cmd **cmd, int *pids)
{
	while(*cmd)
	{
		if (*cmd->fdin || *cmd->fdout || *cmd->heredoc)//todo
			open_file(*cmd);
		create_pipe();
		*pids = fork();
		if (!*pids)
			cmd_proc(data, *cmd);
		else
		{
			// close_stream();
			*cmd = *cmd->next;
			if (!(*cmd || *cmd->op)
				return ;
			pids++;
		}
	}
}

void	open_file(t_cmd *cmd)
{
	if (cmd->type_rdct[0] == RD_HD)
		open(HERED_PATH, O_RDONLY);
	else if (cmd->type_rdct[0] == RD_IN)
		open(cmd->file_path[0], O_RDONLY);
	if (cmd->type_rdct[1] == RD_OUT)
		open(cmd->file_path[1], O_WRONLY | O_TRUNC | O_CREATE 0644)
	else if (cmd->type_rdct[1] == RD_APP)
		open(cmd->file_path[1], O_WRONLY | O_APPEND | O_CREATE 0644)
}

void	create_pipe(t_cmd *cmd)
{
	//
	
}

void	wait_cmdproc(t_data *data, int *pids)
{
	// wait and get status
	// take exit code from status and contain to the struct
}

void	close_stream()
{
	//close fds
	//if heredoc
		//unlink
}
