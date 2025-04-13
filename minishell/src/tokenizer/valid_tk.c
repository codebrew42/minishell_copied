/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_tk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:03:20 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 19:03:21 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		valid_input(t_mshell *ms_data, char *input);
int		valid_parentheses(char *str);
int		valid_quotes(char *str);

int	valid_input(t_mshell *ms_data, char *input)
{
	int			k;

	k = 0;
	if (!input || !valid_quotes(input) || !valid_parentheses(input))
	{
		if (!valid_quotes(input))
		{
			err_syntax(ERR_MSG_QOT, &k);
			free_token_and_reset(&ms_data->tokens);
		}
		if (!valid_parentheses(input))
		{
			err_syntax(ERR_MSG_PAREN, &k);
			free_token_and_reset(&ms_data->tokens);
		}
		return (0);
	}
	return (1);
}

int	valid_parentheses(char *str)
{
	int		i;
	char	quote_type;

	i = 0;
	quote_type = 0;
	while (str[i])
	{
		if (str[i] == '(' && quote_type == 0)
			quote_type = str[i];
		else if (str[i] == ')')
			quote_type = 0;
		i++;
	}
	return (quote_type == 0);
}

int	valid_quotes(char *str)
{
	int		i;
	char	quote_type;

	i = 0;
	quote_type = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote_type == 0)
			quote_type = str[i];
		else if (str[i] == quote_type)
			quote_type = 0;
		i++;
	}
	return (quote_type == 0);
}
