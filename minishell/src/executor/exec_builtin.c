/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:53:31 by ********          #+#    #+#             */
/*   Updated: 2025/04/03 19:43:20 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	exec_builtin(t_mshell *data, t_cmd *cmd, t_cmd *cmd_root)
{
	int	std[2];

	if (cmd->op == OP_PIPE || cmd->pipe_prev[0] || !cmd->bi)
		return (0);
	std[0] = dup(0);
	if (std[0] < 0)
		exit_exec(data, cmd_root);
	std[1] = dup(1);
	if (std[1] < 1)
		exit_exec(data, cmd_root);
	if (cmd->fdin)
		if (set_stdinout(cmd->fdin, 0))
			exit_exec(data, cmd_root);
	if (cmd->fdout)
		if (set_stdinout(cmd->fdout, 1))
			exit_exec(data, cmd_root);
	call_builtin(data, cmd, cmd_root, std);
	if (set_stdinout(std[0], 0))
		exit_exec(data, cmd_root);
	if (set_stdinout(std[1], 1))
		exit_exec(data, cmd_root);
	return (0);
}

int	call_builtin(t_mshell *data, t_cmd *cmd, t_cmd *cmd_root, int *std)
{
	int	ret;

	if (cmd->bi == BI_PWD)
		ret = ms_pwd(data->env_var);
	else if (cmd->bi == BI_CD)
		ret = ms_cd(data->env_var, cmd->args);
	else if (cmd->bi == BI_ECHO)
		ret = ms_echo(cmd->args);
	else if (cmd->bi == BI_ENV)
		ret = ms_env(data->env_var);
	else if (cmd->bi == BI_EXPT)
		ret = ms_export(data, cmd->args);
	else if (cmd->bi == BI_UNSET)
		ret = ms_unset(data, cmd->args);
	else if (cmd->bi == BI_EXIT)
		ret = ms_exit(data, cmd_root, cmd, std);
	if (cmd->child || ret == ERR)
	{
		if (cmd->child)
			free_cmdproc(data, cmd_root);
		if (ret == ERR)
			err_exit(NULL, 0);
		exit(g_exit_status);
	}
	return (ret);
}

t_bltin	isbuiltin(char *s)
{
	if (!ft_strncmp(s, "echo", ft_strlen("echo") + 1))
		return (BI_ECHO);
	else if (!ft_strncmp(s, "cd", ft_strlen("cd") + 1))
		return (BI_CD);
	else if (!ft_strncmp(s, "pwd", ft_strlen("pwd") + 1))
		return (BI_PWD);
	else if (!ft_strncmp(s, "export", ft_strlen("export") + 1))
		return (BI_EXPT);
	else if (!ft_strncmp(s, "unset", ft_strlen("unset") + 1))
		return (BI_UNSET);
	else if (!ft_strncmp(s, "env", ft_strlen("env") + 1))
		return (BI_ENV);
	else if (!ft_strncmp(s, "exit", ft_strlen("exit") + 1))
		return (BI_EXIT);
	return (BI_NONE);
}

void	exit_exec(t_mshell *data, t_cmd *cmd)
{
	free_cmddata(cmd);
	free_mshell(data);
	err_exit(NULL, 0);
}
