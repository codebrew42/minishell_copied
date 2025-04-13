/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_linked_op.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:59:57 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 18:59:58 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	validate_start_end_op(t_ast *ast);
int	validate_linked_operators(t_ast *ast);

int	validate_start_end_op(t_ast *ast)
{
	t_ast	*last;

	if (!ast)
		return (1);
	last = ast;
	while (last->right)
		last = last->right;
	if (is_op_type(ast->type) || is_op_type(last->type))
		return (err_syntax("near operator\n", NULL));
	if (is_redirection_type(ast->type))
		return (err_syntax("near redirection\n", NULL));
	return (1);
}

int	validate_linked_operators(t_ast *ast)
{
	t_ast	*current;
	t_ast	*next;

	if (!ast)
		return (1);
	current = ast;
	while (current)
	{
		next = current->right;
		if (!next)
			break ;
		if (is_op_type(current->type)
			&& (!next
				|| (next->type != TYPE_CMD && next->type != TYPE_PAREN_OPEN)))
			return (err_syntax("near operator\n", NULL));
		if (current->type == TYPE_PIPE && (!next || next->type == TYPE_PIPE))
			return (err_syntax("near `|'\n", NULL));
		current = current->right;
	}
	return (1);
}
