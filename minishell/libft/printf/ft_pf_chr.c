/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_chr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:18:46 by ********          #+#    #+#             */
/*   Updated: 2024/05/26 11:41:23 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_chr(va_list *args, t_form *form, int *outlen)
{
	char	c;

	c = va_arg(*args, int);
	if (form->width > 1)
	{
		if (form->flag[0] == HYPHEN)
			form->sp_end = form->width - 1;
		else
			form->sp_beg = form->width - 1;
	}
	*outlen += (1 + form->sp_beg + form->sp_end);
	while (form->sp_beg--)
		ft_putchar_fd(' ', 1);
	ft_putchar_fd(c, 1);
	while (form->sp_end--)
		ft_putchar_fd(' ', 1);
}
