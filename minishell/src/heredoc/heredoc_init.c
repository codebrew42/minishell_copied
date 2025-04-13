/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:46:51 by ********          #+#    #+#             */
/*   Updated: 2025/03/29 14:24:50 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

static int		count_hdcflag(t_ast *ast);
static void		set_limiters(t_ast *ast, t_heredoc *hdc);

int	init_heredoc(t_mshell *data)
{
	int			n;
	t_heredoc	*tmp;

	n = count_hdcflag(data->ast_root);
	if (!n)
		return (1);
	if (data->hdc)
		free_hdc(data->hdc);
	data->hdc = NULL;
	data->hdc = ft_calloc(1, sizeof(t_heredoc));
	if (!data->hdc)
		return (free_mshell(data), err_exit(NULL, 0), 1);
	tmp = data->hdc;
	while (--n)
	{
		tmp->next = ft_calloc(1, sizeof(t_heredoc));
		if (!tmp->next)
			return (free_mshell(data), err_exit(NULL, 0), 1);
		tmp = tmp->next;
	}
	set_limiters(data->ast_root, data->hdc);
	return (0);
}

static int	count_hdcflag(t_ast *ast)
{
	int	n;

	if (!ast)
		return (0);
	n = 0;
	while (ast)
	{
		if (ast->type == TYPE_REDIR_HDC)
			n++;
		ast = ast->right;
	}
	return (n);
}

static void	set_limiters(t_ast *ast, t_heredoc *hdc)
{
	while (ast)
	{
		if (ast->type == TYPE_REDIR_HDC)
		{
			hdc->lim = ast->args;
			hdc = hdc->next;
		}
		ast = ast->right;
	}
}
