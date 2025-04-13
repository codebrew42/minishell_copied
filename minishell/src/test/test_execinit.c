/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execinit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:37:07 by ********          #+#    #+#             */
/*   Updated: 2025/03/16 17:24:56 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "test_ms.h"

int	main(int ac, char **av, char **envp)
{
	t_mshell	*data;
	t_ast		**tmp;
	char	**args = NULL;
	int		exit;

	if (!ac && av)
		return (1);
	init_mshell(&data, envp);
/*
	args = ft_split("exit 10", ' ');
	tmp = &(data->ast_root);
	set_ast(tmp, TYPE_CMD, &args);

	args = NULL;
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_PIPE, &args);

	args = ft_split("exit 10", ' ');
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_CMD, &args);
	*/
/*
	args = ft_split("cat file", ' ');
	tmp = &(data->ast_root);
	set_ast(tmp, TYPE_CMD, &args);

	args = NULL;
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_PIPE, &args);

	args = ft_split("grep h", ' ');
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_CMD, &args);

	args = NULL;
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_PIPE, &args);

	args = ft_split("wc", ' ');
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_CMD, &args);
	*/

/*
	args = ft_split("pwd", ' ');
	tmp = &(data->ast_root);
	set_ast(tmp, TYPE_CMD, &args);

	//args = ft_split("file", ' ');
	//tmp = &((*tmp)->right);
	//set_ast(tmp, TYPE_REDIR_IN, &args);

	args = NULL;
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_PIPE, &args);

	args = ft_split("grep q", ' ');
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_CMD, &args);
	*/

	/*
	args = NULL;
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_PIPE, &args);

	args = ft_split("grep w", ' ');
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_CMD, &args);
	args = NULL;
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_AND, &args);

	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_PAREN_OPEN, &args);

	args = ft_split("ls", ' ');
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_CMD, &args);

	args = NULL;
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_AND, &args);

	args = ft_split("ls", ' ');
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_CMD, &args);

	args = NULL;
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_PAREN_CLOSE, &args);

	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_AND, &args);

	args = ft_split("ls -a", ' ');
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_CMD, &args);

	args = ft_split("outfile", ' ');
	tmp = &((*tmp)->right);
	set_ast(tmp, TYPE_REDIR_APP, &args);

*/
	testprint_ast(data->ast_root);
	executor(data);
	exit = data->dol_questn;
	free_mshell(data);
	return (exit);
}
