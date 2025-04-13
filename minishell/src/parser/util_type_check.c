/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_type_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:59:50 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 18:59:51 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_not_hdc_type(t_type type);
int	is_paren_type(t_type type);
int	is_op_type(t_type type);
int	is_not_op_or_paren(t_type type);
int	is_redirection_type(t_type type);

int	is_redir_not_hdc_type(t_type type)
{
	return (type == TYPE_REDIR_IN || type == TYPE_REDIR_OUT
		|| type == TYPE_REDIR_APP);
}

int	is_paren_type(t_type type)
{
	return (type == TYPE_PAREN_OPEN || type == TYPE_PAREN_CLOSE);
}

int	is_op_type(t_type type)
{
	return (type == TYPE_PIPE || type == TYPE_AND || type == TYPE_OR);
}

int	is_not_op_or_paren(t_type type)
{
	return (!is_op_type(type) && !is_paren_type(type));
}

int	is_redirection_type(t_type type)
{
	return (type == TYPE_REDIR_IN || type == TYPE_REDIR_OUT
		|| type == TYPE_REDIR_APP || type == TYPE_REDIR_HDC);
}
