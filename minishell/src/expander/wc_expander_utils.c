/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:08:31 by ********          #+#    #+#             */
/*   Updated: 2025/03/25 09:54:34 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

int	filter_line(char *s, char *fil)
{
	if ((!*fil && *s) || (*s != *fil && *fil != '*'))
		return (0);
	while (*fil && *fil == '*' && *(fil + 1) == '*')
		fil++;
	if ((!*s && !*fil) || (*fil && *fil == '*' && !*(fil + 1)))
		return (1);
	if (!*s)
		return (0);
	while (*s && *fil && *s == *fil && *fil != '*')
	{
		s++;
		fil++;
	}
	while (*fil && *s && *fil == '*' && *(fil + 1) != *s)
		s++;
	if (*fil && *s && *fil == '*' && *(fil + 1) == *s)
	{
		if (filter_line(s, fil + 1))
			return (1);
		if (filter_line(s + 1, fil))
			return (1);
		return (0);
	}
	return (filter_line(s, fil));
}

void	rm_lstnode(t_list **lst, t_list *node)
{
	t_list	*tmp;

	tmp = *lst;
	if (*lst == node)
		*lst = node->next;
	else
	{
		while (tmp->next && tmp->next != node)
			tmp = tmp->next;
		tmp->next = node->next;
	}
	ft_lstdelone(node, &free);
}

int	count_lstnode(t_list *lst)
{
	int	n;

	n = 0;
	while (lst)
	{
		lst = lst->next;
		n++;
	}
	return (n);
}
