/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:00:53 by ********          #+#    #+#             */
/*   Updated: 2025/02/17 18:42:59 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//split the token and build a linked list.
void	tokenizer(t_data *data, char *input)
{
	int	t_len;
	int	t_count;
	t_token	*tmp;

	t_count = count_token(); // if error (not closed quots) return -1
	if (t_count < 0)
		err_exit("wrong input");
	tmp = data->token;
	while (t_count--)
	{
		t_len = token_len();
		tmp = malloc(sizeof(t_taken) + 1);
		if (!tmp)
			err_exit();
		input[t_len] = 0;
		tmp->name = strdup(input);
		if (!tmp->name)
			err_exit();
		input[t_len] = ' ';
		if (!next_token(input)) // if there is more token,m set pointer to the first char of the next token
			break ;
		tmp = tmp->next;
	}
}
