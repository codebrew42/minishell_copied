/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:04:33 by ********          #+#    #+#             */
/*   Updated: 2025/03/30 20:28:15 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

sig_atomic_t	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_mshell *data;
	t_ast	*tmp;
	int	i;

	if (!ac || !av)
		return (1);
	init_mshell(&data, envp);
//	testprint_env(data->env_var);
	data->ast_root = ft_calloc(1, sizeof(t_ast));
	if (!data->ast_root)
		return (1);
	tmp = data->ast_root;
	tmp->type = TYPE_REDIR_HDC;
	//tmp->args = ft_split("L", ' ');
	tmp->args = ft_split("L1 L2 L3", ' ');
	i  = 2;
	while (i--)
	{
		tmp->right = ft_calloc(1, sizeof(t_ast));
		if (!tmp->right)
			return (1);
		tmp = tmp->right;
		tmp->type = TYPE_REDIR_HDC;
		tmp->args = ft_split("L", ' ');
	}
	ms_heredoc(data);
	/*
	char	buff[100];//test
	printf("read: %ld\n", read(hdc->fd, buff, 100));
	printf("hdc file: %s\n", buff);
	printf("fd: %d\n", data->hdc->fd);
	printf("file: %s\n", data->hdc->filename);
	*/
	free_mshell(data);
	return (0);
}

void	testprint_env(t_env *env)
{
	while (env)
	{
		printf("key: %s\n", env->key);
		printf("value: %s\n", env->value);
		puts("\n");
		env = env->next;
	}
}

/*
void	testprint_lst(t_list *lst)
{
	if (!lst)
		return ;
	printf("content: %s\n", (char *)(lst->content));
	testprint_lst(lst->next);
}
*/
