/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:27:29 by ********          #+#    #+#             */
/*   Updated: 2025/02/26 16:39:51 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_heredoc(t_data *data, char *lim)
{
	char	*input;

	while(1)
	{
		input = readline("> ");
		if (!input)
			break ;
		else if (!ft_strcmp(input, lim, ft_strlen(lim) + 1))
		{
			free(input);
			break ;
		}
		if (create_list(&(data->heredoc), input))
			err_exit();
	}
}

//for libft
void	create_list(t_list **list, char *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		err_exit();
	if (!*list)
		*list = new;
	else
		ft_lstadd_back(list, new);
}
