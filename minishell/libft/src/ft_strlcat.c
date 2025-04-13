/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:50:56 by ********          #+#    #+#             */
/*   Updated: 2024/05/08 23:27:06 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;

	d_len = ft_strlen(dst);
	s_len = ft_strlen((char *)src);
	if (size == 0 || d_len > size)
		return (size + s_len);
	dst += d_len;
	size -= d_len;
	while (size-- > 1 && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (d_len + s_len);
}
