/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmdproc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:52:51 by ********          #+#    #+#             */
/*   Updated: 2025/03/01 18:46:58 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#incldue "minishell.h"

int	cmd_proc(t_data *data, t_cmd *cmd)
{
	t_buildin	bi;
	
	set_stream(cmd);
	bi = isbuildin();
	if (bi)
	{
		excute_buildin();
		//close fds
		//free
		//exit
	}
	else (!bi)
		if (check_cmd())
			if (!cmd->path)
				err_exit("Command not found.");
	if (execve(cmd->path, cmd->args, data->envp))
		err_exit(NULL);
}

void	set_stream(t_cmd *cmd)
{
	//close unnecessary pipe
	if (cmd->pipe[0])
		close(cmd->pipe[0]);
	//connect with stdin/out
	if (cmd->fdin)
		//set to stdin
	else
		//set pipe to stdin
	if (cmd->fout)
		// set to stdout
	else
		//set pipe to stdout
}

void	check_cmd(t_cmd *cmd, char **path)
{
	char	*fullp;

	path = data->path;
	while (tmp)
	{
		fullp = ft_strjoin(*path, cmd->args[0]);
		if (!fullp)
			//free, err_exit
		if (!access())
		{
			cmd->path  = fullp;
			return (0);
		}
		else
			free(fullp);
	}
}

void	excute_buildin(t_data *data, t_cmd *cmd, t_buildin bi)
{
	if (bi == BI_ECHO)
		bi_echo();
	// if (cd)
	// 	call cd
	// etc.
}
