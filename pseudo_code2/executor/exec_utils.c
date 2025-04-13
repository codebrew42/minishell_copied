/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:44:52 by ********          #+#    #+#             */
/*   Updated: 2025/02/28 21:48:52 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_ast *ast)
{
	int	n;

	if (!ast)
		return (ERR);
	n = 0;
	while(1)
	{
		if (ast->type == TK_WORD)
			n++;
		if (ast->nexto)
			ast = ast->next;
		else
			break;
	}
	return (n);
}

t_buildin	isbuildin(char *s)
{
	if (ft_strcmp(s, "echo", 5))
		return (BI_ECHO);
	//if cd
		return (BI_CD);
	//etc.
}

void	free_exec(t_cmd *cmds)
{
	//free cmds
}
