/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:34:25 by ********          #+#    #+#             */
/*   Updated: 2025/03/25 21:48:46 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

void	handl_wildcard(t_mshell *data, t_ast *ast)
{
	while (ast)
	{
		if (check_args_wc(&(ast->args)))
		{
			free_mshell(data);
			err_exit(NULL, 0);
		}
		ast = ast->next;
	}
}

int	check_args_wc(char ***args)
{
	char	**tmp;
	char	**wc_args;

	tmp = *args;
	while(tmp)
	{
		if (strchr(tmp, '*'))
			if (!wc_check_quotes())//todo
				wc_args = wc_expander();
		if (!wc_args)
			return (ERR);
		wc_rebuild_args(args, wc_args);//todo
		free(wc_args);
	}
}
