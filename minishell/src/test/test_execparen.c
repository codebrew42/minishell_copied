/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execparen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:05:38 by ********          #+#    #+#             */
/*   Updated: 2025/03/18 14:52:11 by ********         ###   ########.fr       */
/*   Updated: 2025/03/16 18:04:05 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "test_ms.h"
int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_mshell	*data;
	t_ast		**tmp;
	int		exit;

	if (!ac && av)
		return (1);
	init_mshell(&data, envp);
	tmp = &(data->ast_root);

/*
	lst_add_ast(tmp, TYPE_CMD, "cat file");
	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_AND, NULL);
	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_CMD, "cat file");
	*/

	lst_add_ast(tmp, TYPE_PAREN_OPEN, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_PAREN_OPEN, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_PAREN_OPEN, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_CMD, "cat file");

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_PIPE, NULL);


	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_CMD, "wc");

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_OR, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_CMD, "false");

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_PAREN_CLOSE, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_AND, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_CMD, "pwd");

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_PAREN_CLOSE, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_AND, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_CMD, "ls");

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_AND, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_PAREN_OPEN, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_CMD, "echo hello");

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_OR, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_CMD, "pwd");

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_PAREN_CLOSE, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_PAREN_CLOSE, NULL);

	/*
//	args = ft_split("exit 10", ' ');
	args = NULL;
	tmp = &(data->ast_root);
	lst_add_ast(tmp, TYPE_PAREN_OPEN, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_PAREN_OPEN, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_CMD, "pwd");

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_AND, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_CMD, "wc");

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_PAREN_CLOSE, NULL);

	tmp = &((*tmp)->right);
	lst_add_ast(tmp, TYPE_PAREN_CLOSE, NULL);
	args = NULL;
	tmp = &(data->ast_root);
	set_ast(tmp, TYPE_PAREN_CLOSE, &args);
	*/

/*
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

