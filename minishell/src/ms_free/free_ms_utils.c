/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:43:58 by ********          #+#    #+#             */
/*   Updated: 2025/03/11 23:17:45 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **mtx, int idx);
void	free_strarr(char **arr);
void	free_token_and_reset(t_token **t);

void	free_matrix(char **mtx, int idx)
{
	if (!mtx)
		return ;
	if (!mtx[idx])
	{
		free(mtx[idx]);
		return ;
	}
	free_matrix(mtx, idx + 1);
	free(mtx[idx]);
	if (!idx)
		free(mtx);
}

void	free_strarr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_token_and_reset(t_token **t)
{
	t_token	*current;
	t_token	*next;

	if (!t || !*t)
		return ;
	current = *t;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*t = NULL;
}
