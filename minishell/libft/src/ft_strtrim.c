/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 21:16:33 by ********          #+#    #+#             */
/*   Updated: 2024/05/08 23:43:59 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*result;

	if (!set || !s1)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	if (!*s1)
		return (ft_strdup(""));
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[len -1]))
		len--;
	result = ft_substr(s1, 0, len);
	if (!result)
		return (NULL);
	return (result);
}
