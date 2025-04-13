/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_cmd_with_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:59:37 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 18:59:38 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int		has_embedded_redirs(t_token *tokens);
int		save_args_skip_redir(t_token **tokens, t_ast *cmd_node, t_token *start);
int		count_actual_args(t_token *start);
int		process_redirections(t_token *start, t_ast **last_node);
t_ast	*create_redir_node(t_token *redir, t_token *target, t_ast **last_node);

int	has_embedded_redirs(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (!tmp || tmp->type != TYPE_TMP_WORD)
		return (0);
	while (tmp && tmp->type == TYPE_TMP_WORD)
		tmp = tmp->next;
	if (tmp && is_redirection_type(tmp->type) && tmp->type != TYPE_REDIR_HDC
		&& tmp->next && tmp->next->type == TYPE_TMP_WORD)
		return (1);
	return (0);
}

int	save_args_skip_redir(t_token **tokens, t_ast *cmd_node, t_token *start)
{
	t_token	*tmp;
	int		i;

	cmd_node->args = ft_calloc(count_actual_args(start) + 1, sizeof(char *));
	if (!cmd_node->args)
		return (0);
	i = 0;
	tmp = start;
	while (tmp && is_not_op_or_paren(tmp->type))
	{
		if (tmp->type == TYPE_TMP_WORD
			&& (tmp == start || !is_redirection_type(tmp->prev->type)))
		{
			cmd_node->args[i] = ft_strdup(tmp->value);
			if (!cmd_node->args[i])
				return (free_strarr(cmd_node->args), cmd_node->args = NULL, 0);
			i++;
		}
		tmp = tmp->next;
	}
	tmp = start;
	while (tmp && tmp->next && is_not_op_or_paren(tmp->next->type))
		tmp = tmp->next;
	*tokens = tmp;
	return (1);
}

int	count_actual_args(t_token *start)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = start;
	while (tmp && !is_op_type(tmp->type) && !is_paren_type(tmp->type))
	{
		if (tmp->type == TYPE_TMP_WORD
			&& (tmp == start || !is_redirection_type(tmp->prev->type)))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	process_redirections(t_token *start, t_ast **last_node)
{
	t_token	*tmp;
	t_ast	*redir_node;

	tmp = start;
	while (tmp && !is_op_type(tmp->type) && !is_paren_type(tmp->type))
	{
		if (is_redirection_type(tmp->type) && tmp->next
			&& tmp->next->type == TYPE_TMP_WORD)
		{
			redir_node = create_redir_node(tmp, tmp->next, last_node);
			if (!redir_node)
				return (0);
			*last_node = redir_node;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

t_ast	*create_redir_node(t_token *redir, t_token *target, t_ast **last_node)
{
	t_ast	*node;

	node = create_ast_node(redir->type);
	if (!node)
		return (NULL);
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = ft_strdup(target->value);
	if (!node->args[0])
	{
		free(node->args);
		free(node);
		return (NULL);
	}
	node->args[1] = NULL;
	(*last_node)->right = node;
	return (node);
}
