/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:57:57 by ********          #+#    #+#             */
/*   Updated: 2025/03/17 21:06:02 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "test_ms.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_mshell	*data;
	char		**args;

	init_mshell(&data, envp);

	args = NULL;
	args = ft_split("export test2=aaa PATH=bbb:ccc", ' ');
	if (!args)
		err_exit(NULL, 0);
	ms_export(data, args);
	if (find_print_env(data->env_var, "test2"))
		printf("%s is not in env\n", args[1]);
//	if (find_print_env(data->env_var, "test3"))
//		printf("%s is not in env\n", args[2]);
		
	puts("path:");
	print_path(data->path);

	free_matrix(args, 0);
	free_mshell(data);
	return (0);
}
