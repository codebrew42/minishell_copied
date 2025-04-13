/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:04:16 by ********          #+#    #+#             */
/*   Updated: 2024/05/30 14:47:30 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_str(const char *s, va_list *args, int *outlen)
{
	while (*s)
	{
		if (*s != '%')
		{
			ft_putchar_fd(*s++, 1);
			(*outlen)++;
		}
		else
		{
			if (*(s + 1) != '%')
			{
				s = ft_parse_format(++s, args, outlen);
				if (!s)
					return ;
			}
			else
			{
				ft_putchar_fd(*s, 1);
				(*outlen)++;
				s += 2;
			}
		}
	}
}
