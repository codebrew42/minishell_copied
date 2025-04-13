/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:42:26 by ********          #+#    #+#             */
/*   Updated: 2025/04/03 20:52:14 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

int	count_linelen(t_list *lst)
{
	int	n;

	n = 0;
	while (lst)
	{
		n += ft_strlen((char *)lst->content);
		lst = lst->next;
	}
	return (n);
}

char	*set_next_p(char *line)
{
	char	*p;

	p = line;
	if (*line == '$')
	{
		p++;
		if (!ft_strncmp(p, "?", 1))
			return (++p);
		else
			while (*p && ft_isalnum(*p))
				p++;
	}
	else if (*line != '$')
		p = ft_strchr(line, '$');
	if (!p)
		p = line + ft_strlen(line);
	return (p);
}

int	check_dol_questn(char *key, char **envval, int excode)
{
	if (!ft_strncmp(key, "?", 2))
	{
		*envval = ft_itoa(excode);
		if (!*envval)
			return (ERR);
	}
	return (0);
}
