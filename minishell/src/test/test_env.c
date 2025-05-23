/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:07:27 by ********          #+#    #+#             */
/*   Updated: 2025/03/15 22:14:42 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_mshell *data;

	init_mshell(&data, envp);
	ms_env(data->env_var);
	return (0);
}
