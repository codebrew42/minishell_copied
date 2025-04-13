/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:07:43 by ********          #+#    #+#             */
/*   Updated: 2025/04/02 20:52:29 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	ms_echo(char **av)
{
	int	op_n;
	int	ac;

	ac = 0;
	while (av[ac])
		ac++;
	op_n = 0;
	if (*(++av) && !ft_strncmp(*av, "-n", 3))
	{
		op_n = 1;
		av++;
		ac--;
	}
	if (ac)
	{
		while (--ac)
		{
			ft_putstr_fd(*av++, 1);
			if (ac > 1)
				ft_putchar_fd(' ', 1);
		}
	}
	if (!op_n)
		write(1, "\n", 1);
	return (0);
}
