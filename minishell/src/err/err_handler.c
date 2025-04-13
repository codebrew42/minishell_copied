/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:15:10 by ********          #+#    #+#             */
/*   Updated: 2025/04/02 17:07:12 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_exit(char *s, int excode);
void	err_cmd(char *cmd);
int		err_syntax(char *input, int *i);

// if using errno, s = NULL, excode = 0
void	err_exit(char *s, int excode)
{
	if (!s)
		perror("minishell");
	else
	{
		write(2, "minishell: ", 11);
		ft_putendl_fd(s, 2);
	}
	if (excode)
		exit(excode);
	exit(errno);
}

void	err_msg(char *msg, char *name)
{
	ft_putstr_fd("minishell: ", 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

void	errno_msg(char *cmd, char *name)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errno), 2);
}

int	err_syntax(char *input, int *i)
{
	int	k;

	write(2, "minishell: ", 11);
	if (input && i && *i != 0)
	{
		if (*i == OP_SYNTAX_INVALID)
			*i = 2;
		ft_putstr_fd(ERR_MSG_SYNTAX_ARG, 2);
		k = 0;
		while (k < *i)
		{
			ft_putchar_fd(input[k], 2);
			k++;
		}
		ft_putendl_fd("'", 2);
	}
	else if (input && (!i || *i == 0))
	{
		ft_putstr_fd("syntax error ", 2);
		ft_putstr_fd(input, 2);
	}
	return (0);
}

void	errno_exit(t_mshell *data)
{
	free_mshell(data);
	err_exit(NULL,0);
}
