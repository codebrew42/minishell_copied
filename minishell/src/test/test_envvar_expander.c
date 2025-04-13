/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_envvar_expander.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:06 by ********          #+#    #+#             */
/*   Updated: 2025/03/18 15:05:58 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test_ms.h"
#include "expander.h"

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_mshell	*data;
	init_mshell(&data, envp);
	char	*line;

	(void)ac;
	(void)av;
	line = ft_strdup("$PATH$?a$?");
	if (line)
	{
		line = ev_expander(data, line);
		printf("%s\n", line);
		free(line);
	}
	free_mshell(data);
	return (0);
}

