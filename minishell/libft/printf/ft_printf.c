/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:22:38 by ********          #+#    #+#             */
/*   Updated: 2024/05/30 17:26:38 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		outlen;

	if (!s)
		return (-1);
	outlen = 0;
	va_start(args, s);
	ft_parse_str(s, &args, &outlen);
	va_end(args);
	return (outlen);
}
