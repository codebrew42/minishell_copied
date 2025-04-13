/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:51:46 by ********          #+#    #+#             */
/*   Updated: 2024/05/29 21:43:38 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_nil(t_form *form, int *outlen);

void	ft_pf_ptr(va_list *args, t_form *form, int *outlen)
{
	unsigned long	n;
	int				hexlen;

	n = va_arg(*args, unsigned long);
	if (!n)
	{
		ft_put_nil(form, outlen);
		return ;
	}
	form->hsign = 1;
	hexlen = ft_hexlen(n);
	if (form->width > hexlen + 2)
	{
		if (form->flag[0] == HYPHEN)
			form->sp_end = form->width - (hexlen + 2);
		else
			form->sp_beg = form->width - (hexlen + 2);
	}
	*outlen += hexlen + 2 + form->sp_beg + form->sp_end;
	ft_put_hexform(form, n);
}

static void	ft_put_nil(t_form *form, int *outlen)
{
	if (form->width > 5)
	{
		if (form->flag[0] != HYPHEN)
		{
			form->sp_beg = form->width - 5;
			*outlen += form->sp_beg;
		}
		else
		{
			form->sp_end = form->width - 5;
			*outlen += form->sp_end;
		}
	}
	ft_put_strform("(nil)", form, 5);
	*outlen += 5;
}
