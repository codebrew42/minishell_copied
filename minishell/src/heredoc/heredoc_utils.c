/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:49:34 by ********          #+#    #+#             */
/*   Updated: 2025/03/31 08:40:40 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	create_hdc_file(t_heredoc *hdc)
{
	static int	n;
	char		*s;

	n++;
	s = ft_itoa(n);
	if (!s)
		return (ERR);
	hdc->filename = ft_strjoin(HDC_FILE, s);
	if (!hdc->filename)
		return (ERR);
	free(s);
	hdc->fd = open(hdc->filename, \
	O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
	if (hdc->fd == ERR)
		return (ERR);
	return (0);
}

void	clean_hdc(t_mshell *data)
{
	t_heredoc	*tmp;

	tmp = data->hdc;
	while (tmp)
	{
		if (tmp->fd)
			close(tmp->fd);
		tmp = tmp->next;
	}
	free_hdc(data->hdc);
	data->hdc = NULL;
}
