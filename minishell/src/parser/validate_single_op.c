/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_single_op.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:00:02 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 19:00:03 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	validate_ast(t_ast **ast, t_token **tokens, t_token *head);
int	validate_nodes_with_arg(t_ast *ast);
int	validate_parentheses_nodes(t_ast *ast);

int	validate_ast(t_ast **ast, t_token **tokens, t_token *head)
{
	if (!*ast)
		return (1);
	if (!validate_nodes_with_arg(*ast) || !validate_parentheses_nodes(*ast)
		|| !validate_linked_operators(*ast) || !validate_start_end_op(*ast))
	{
		free_ast(*ast);
		*tokens = head;
		*ast = NULL;
		return (0);
	}
	return (1);
}

int	validate_nodes_with_arg(t_ast *ast)
{
	t_ast	*current;

	current = ast;
	while (current)
	{
		if (is_redirection_type(current->type))
		{
			if (!current->args)
				return (err_syntax("near redirection\n", NULL));
			if (!current->args[0] || *(current->args[0]) == '\0')
				return (err_syntax("near redirection\n", NULL));
		}
		current = current->right;
	}
	return (1);
}

int	validate_parentheses_nodes(t_ast *ast)
{
	t_ast	*current;
	int		paren_count;
	int		err;

	current = ast;
	paren_count = 0;
	err = 0;
	while (current && !err)
	{
		if (current->type == TYPE_PAREN_OPEN)
		{
			paren_count++;
			err = (current->right && current->right->type == TYPE_PAREN_CLOSE);
		}
		else if (current->type == TYPE_PAREN_CLOSE)
		{
			paren_count--;
			err = (paren_count < 0);
		}
		current = current->right;
	}
	if (paren_count != 0 || err)
		return (err_syntax("near parentheses\n", NULL));
	return (1);
}
