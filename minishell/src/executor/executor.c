/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:16:44 by ********          #+#    #+#             */
/*   Updated: 2025/04/03 20:44:35 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	executor(t_mshell *data)
{
	t_cmd	*cmds;
	int		*pids;
	int		proc_count;

	setup_signals(SIGNAL_MODE_PARENT_WAITING);
	if (g_exit_status)
		return (0);
	cmds = NULL;
	pids = NULL;
	if (check_paren(data->ast_root))
		return (ERR);
	proc_count = init_executor(data, &cmds, &pids);
	cmds->pids = pids;
	//testprint_cmds(cmds);//test
	if (proc_count > 0)
		exec_cmds(data, cmds, pids);
	free_cmddata(cmds);
	if (pids)
		free(pids);
	if (proc_count == ERR)
		err_exit(NULL, 0);
	return (0);
}

int	exec_cmds(t_mshell *data, t_cmd *cmds, int *pids)
{
	int		proc_count;
	t_cmd	*tmp;

	tmp = cmds;
	proc_count = count_cmdlst(cmds);
	while (tmp)
	{
		if (tmp->paren[0])
		{
			if (create_subshell(data, cmds, &tmp, pids) || !tmp)
				break ;
		}
		if (tmp != cmds && !op_check(&tmp, data->dol_questn))
			break ;
		if (create_cmdproc(data, &tmp, cmds, pids))
			return (ERR);
		wait_cmdproc(data, pids);
		ft_bzero(pids, sizeof(int) * proc_count);
		if (!tmp || tmp->paren[1])
			break ;
	}
	if (cmds->child)
		return (free(pids), free_cmdproc(data, cmds), exit(0), 0);
	return (g_exit_status);
}

int	create_subshell(t_mshell *data, t_cmd *cmds, t_cmd **tmp, int *pids)
{
	(*tmp)->paren[0]--;
	*pids = fork();
	if (*pids < 0)
		return (ERR);
	else if (!*pids)
	{
		cmds->child = 1;
		exec_cmds(data, *tmp, pids);
	}
	(*tmp)->paren[0]++;
	moveto_parenend(tmp);
	wait_cmdproc(data, pids);
	return (0);
}

int	create_cmdproc(t_mshell *data, t_cmd **cmd, t_cmd *cmd_root, int *pids)
{
	(*cmd)->pids = pids;
	while (*cmd)
	{
		if (open_file(*cmd) == ERR || create_pipe(*cmd) == ERR)
			return (ERR);
		if (*cmd == cmd_root && (*cmd)->bi && (*cmd)->op != OP_PIPE)
			exec_builtin(data, *cmd, cmd_root);
		else if (!g_exit_status)
		{
			*pids = fork();
			if (*pids < 0)
				return (close_pstream(*cmd), ERR);
			if (!*pids)
				cmd_proc(data, *cmd, cmd_root);
		}
		close_pstream(*cmd);
		if ((*cmd)->paren[1])
			break ;
		*cmd = (*cmd)->next;
		if (!*cmd || (*cmd)->op == OP_AND || (*cmd)->op == OP_OR)
			break ;
		pids++;
	}
	return (0);
}

void	wait_cmdproc(t_mshell *data, int *pids)
{
	int	status;

	status = 0;
	while (*pids)
	{
		waitpid(*pids, &status, 0);
		pids++;
	}
	if (WIFSIGNALED(status))
		data->dol_questn = WTERMSIG(status) + 128;
	else
		data->dol_questn = WEXITSTATUS(status);
//	printf("exit code: %d\n", data->dol_questn);
	if (g_exit_status == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}

/*by jin for testing
void	wait_cmdproc(t_mshell *data, int *pids)
{
	int	status;

	status = 0;
	while (*pids)
	{
		waitpid(*pids, &status, 0);
		if (WIFEXITED(status))  // Normal exit
			data->dol_questn = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))  // Signal termination
			data->dol_questn = 128 + WTERMSIG(status);
		pids++;
	}
	g_exit_status = data->dol_questn;
}
*/