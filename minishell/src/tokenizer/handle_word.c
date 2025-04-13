/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:03:01 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 19:03:02 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_quoted_word(t_mshell *ms, char *input, int *i);
static int	handle_regular_word(t_mshell *ms, char *input, int *i);
static int	find_word_end(char *input, int start);

int	handle_word(t_mshell *ms, char *input, int *i)
{
	int	res;

	if (input[*i] == '"' || input[*i] == '\'')
		res = handle_quoted_word(ms, input, i);
	else
		res = handle_regular_word(ms, input, i);
	if (res == -1)
		return (1);
	return (0);
}

static int	handle_quoted_word(t_mshell *ms, char *input, int *i)
{
	int		j;
	char	*value;
	char	quote_char;

	j = *i;
	quote_char = input[j++];
	while (input[j])
	{
		j++;
		if (input[j - 1] == quote_char)
			break ;
	}
	value = ft_substr(input, *i, j - *i);
	if (!value)
		return (-1);
	if (add_token(ms, TYPE_TMP_WORD, value) < 0)
	{
		free(value);
		return (-1);
	}
	free(value);
	*i = j - 1;
	return (0);
}

static int	handle_regular_word(t_mshell *ms, char *input, int *i)
{
	int		j;
	char	*value;

	j = find_word_end(input, *i);
	if (j <= *i)
		return (0);
	value = ft_substr(input, *i, j - *i);
	if (!value)
		return (-1);
	if (add_token(ms, TYPE_TMP_WORD, value) < 0)
	{
		free(value);
		return (-1);
	}
	free(value);
	*i = j - 1;
	return (0);
}

static int	find_word_end(char *input, int start)
{
	int		i;
	char	quote_char;
	int		in_quotes;

	i = start;
	in_quotes = 0;
	quote_char = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"')
			&& (!in_quotes || (in_quotes && input[i] == quote_char)))
		{
			if (!in_quotes)
				quote_char = input[i];
			in_quotes = !in_quotes;
			i++;
			continue ;
		}
		if (!in_quotes && ft_strchr(" |<>&()\t\n", input[i]))
			break ;
		i++;
	}
	return (i);
}
