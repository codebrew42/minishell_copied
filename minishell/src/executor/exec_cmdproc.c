/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmdproc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:52:51 by ********          #+#    #+#             */
/*   Updated: 2025/04/03 19:43:14 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	cmd_proc(t_mshell *data, t_cmd *cmd, t_cmd *cmd_root)
{
	setup_signals(SIGNAL_MODE_CHILD);
	cmd->child = 1;
	if (set_cstream(cmd))
	{
		free_cmdproc(data, cmd_root);
		err_exit(NULL, 0);
	}
	if (cmd->bi)
	{
		call_builtin(data, cmd, cmd_root, NULL);
		free_cmdproc(data, cmd_root);
		exit(g_exit_status);
	}
	else if (!g_exit_status && check_cmd(data, cmd, cmd_root))
		err_cmd(data, cmd_root, cmd->args[0]);
	if (!g_exit_status && execve(cmd->path, cmd->args, data->envp))
	{
		free_cmdproc(data, cmd_root);
		err_exit(NULL, 0);
	}
	free_cmdproc(data, cmd_root);
	exit (g_exit_status);
}

int	set_cstream(t_cmd *cmd)
{
	if (cmd->pipe[0])
	{
		close(cmd->pipe[0]);
		if (set_stdinout(cmd->pipe[1], 1))
			return (ERR);
	}
	else if (cmd->fdout)
	{
		if (set_stdinout(cmd->fdout, 1))
			return (ERR);
	}
	if (cmd->pipe_prev[0])
	{
		if (set_stdinout(*cmd->pipe_prev[0], 0))
			return (ERR);
	}
	else if (cmd->fdin)
		if (set_stdinout(cmd->fdin, 0))
			return (ERR);
	return (0);
}

int	check_cmd(t_mshell *data, t_cmd *cmd, t_cmd *cmd_rt)
{
	char	*fullp;
	char	**path;

	if (!cmd->args[0][0])
		return (1);
	if (!access(cmd->args[0], F_OK | X_OK))
	{
		cmd->path = ft_strdup(cmd->args[0]);
		return (0);
	}
	path = data->path;
	while (*path)
	{
		fullp = create_pathstr(*path, cmd->args[0]);
		if (!fullp)
			return (free_cmdproc(data, cmd_rt), err_exit(NULL, 0), 1);
		if (g_exit_status || !access(fullp, F_OK | X_OK))
		{
			cmd->path = fullp;
			return (0);
		}
		free(fullp);
		path++;
	}
	return (1);
}

char	*create_pathstr(char *path, char *cmd)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	path = tmp;
	tmp = ft_strjoin(path, cmd);
	if (!tmp)
		return (free(path), NULL);
	free(path);
	return (tmp);
}
