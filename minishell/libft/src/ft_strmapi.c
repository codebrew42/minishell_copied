/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 22:22:21 by ********          #+#    #+#             */
/*   Updated: 2024/05/03 22:22:37 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	char			*c;
	unsigned int	idx;

	result = malloc(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	c = result;
	idx = 0;
	while (*s)
		*c++ = f(idx++, *s++);
	*c = '\0';
	return (result);
}
