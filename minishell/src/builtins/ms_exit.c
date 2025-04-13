/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:12:17 by ********          #+#    #+#             */
/*   Updated: 2025/03/18 18:53:20 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

static void	check_args(char **args, int *excode);
static int	arg_isdigit(char *s);

int	ms_exit(t_mshell *data, t_cmd *cmd_root, t_cmd *cmd, int *std)
{
	int	excode;

	ft_putendl_fd("exit", 1);
	check_args(cmd->args, &excode);
	if (!cmd->child)
		free(cmd->pids);
	close_pstream(cmd);
	if (std)
	{
		close(std[0]);
		close(std[1]);
	}
	free_cmddata(cmd_root);
	free_mshell(data);
	exit(excode);
}

static void	check_args(char **args, int *excode)
{
	int	n;

	n = count_args(args);
	if (n == 1)
		*excode = 0;
	else if (n == 2 && arg_isdigit(args[1]))
		*excode = ft_atoi(args[1]);
	else if (!arg_isdigit(args[1]))
	{
		err_msg(ERR_EXIT_NUM, NULL);
		*excode = 2;
	}
	else
	{
		err_msg(ERR_EXIT_ARG, NULL);
		*excode = 1;
	}
}

static int	arg_isdigit(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s++))
			return (0);
	}
	return (1);
}
