/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:34:33 by ********          #+#    #+#             */
/*   Updated: 2025/03/01 18:52:43 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#incldue "minishell.h"

void	executor(t_data *data)
{
	t_cmd	*cmds;
	t_cmd	*tmp;
	int	*pids;
	int	n_cmd;

	cmds = NULL;
	pids = NULL;
	//set_signal()
	n_cmd = init_executor(data &cmds, &pids);
	if (n_cmd == ERR)
		err_exit(NULL);
	tmp = cmds;
	while(tmp)
	{
		n_cmd = create_cmdproc(data, &tmp, pids);
		if (n_cmd < 0)
			err_exit(NULL);
		wait_cmdproc(data, pids);
		ft_bzero(pids, sizeof(int) * n_cmd);
	}
	free_cmd_data();
	free(pids);
}

int	init_excutor(t_mshell *data, t_cmd **cmds, int **pids)
{
	int	n_cmd;
	int	i;
	t_cmd	*tmp;

	n_cmd = count_cmd(data->ast);
	*pids = ft_calloc(n_cmd, sizeof(int));
	tmp = *cmds;
	i = n_cmd
	while (i--)
	{
		tmp = ft_calloc(1, sizeof(t_cmd));
		if (!tmp)
			return (free_exec(*cmds), ERR);
		tmp = tmp->next;
	}
	
	set_cmddata(data->ast, *cmds);
	return (n_cmd);
}

void	set_cmddata(t_ast *ast, t_cmd *cmds)
{
	//go through the ast and set data to cmds
}
