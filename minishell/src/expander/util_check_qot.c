/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_check_qot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:00:20 by jiepark           #+#                    */
/*   Updated: 2025/04/03 19:00:23 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	surrounded_by_single_quotes(char *arg)
{
	return (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'');
}

int	has_quotes(char *arg)
{
	return (ft_strchr(arg, '\'') || ft_strchr(arg, '\"'));
}

int	has_nested_quotes(char *arg)
{
	return (ft_strchr(arg, '\'') && ft_strchr(arg, '\"'));
}

int	get_outer_quote_type(const char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if (str[0] == '\'' && str[len - 1] == '\'')
	{
		if (len == 2)
			return (BLANK_IN_QUOTE);
		return (SINGLE_QUOTE);
	}
	else if (str[0] == '"' && str[len - 1] == '"')
	{
		if (len == 2)
			return (BLANK_IN_QUOTE);
		return (DOUBLE_QUOTE);
	}
	return (0);
}

int	needs_processing(const char *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"' || arg[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
