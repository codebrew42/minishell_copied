/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:03:08 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 19:03:09 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		tokenizer(t_mshell *ms_data, char *input);
void	save_token_data(t_mshell *ms, t_token *tmp_token);
int		add_token(t_mshell *ms, int type, char *value);

int	tokenizer(t_mshell *ms_data, char *input)
{
	int	i;

	if (!valid_input(ms_data, input))
		return (1);
	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (ft_strchr("|<>&()", input[i]))
		{
			if (handle_operator(ms_data, input, &i) == -1)
				return (1);
			continue ;
		}
		if (handle_word(ms_data, input, &i))
			return (1);
		i++;
	}
	return (0);
}

void	save_token_data(t_mshell *ms, t_token *tmp_token)
{
	t_token	*head;

	if (!ms->tokens)
		ms->tokens = tmp_token;
	else
	{
		head = ms->tokens;
		while (ms->tokens->next)
			ms->tokens = ms->tokens->next;
		tmp_token->prev = ms->tokens;
		ms->tokens->next = tmp_token;
		ms->tokens = head;
	}
}

int	add_token(t_mshell *ms, int type, char *value)
{
	t_token		*tmp_token;
	int			len;

	tmp_token = malloc(sizeof(t_token));
	if (!tmp_token)
		err_exit(ERR_MSG_MEM, 1);
	tmp_token->type = type;
	len = ft_strlen(value);
	tmp_token->value = malloc(len + 1);
	if (!tmp_token->value)
	{
		free(tmp_token);
		err_exit(ERR_MSG_MEM, 1);
	}
	ft_memcpy(tmp_token->value, value, len);
	tmp_token->value[len] = '\0';
	tmp_token->next = NULL;
	tmp_token->prev = NULL;
	save_token_data(ms, tmp_token);
	return (len);
}
