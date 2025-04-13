/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:47:05 by ********          #+#    #+#             */
/*   Updated: 2024/05/29 21:11:02 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_flag_sort(t_form *form);
static void	ft_calc_printcond(t_form *form, int hexlen);

void	ft_pf_hex(va_list *args, t_form *form, int *outlen)
{
	unsigned int	n;
	int				hexlen;

	n = va_arg(*args, unsigned int);
	if (!n && !form->prec)
		hexlen = 0;
	else
		hexlen = ft_hexlen(n);
	ft_calc_printcond(form, hexlen);
	*outlen += hexlen + form->zero + form->sp_beg + form->sp_end;
	if (n && form->hsign)
		*outlen += 2;
	ft_put_hexform(form, n);
}

int	ft_hexlen(unsigned long n)
{
	int	len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		len++;
		n = n >> 4;
	}
	return (len);
}

static void	ft_calc_printcond(t_form *form, int hexlen)
{
	if (form->prec > hexlen)
		form->zero = form->prec - hexlen;
	if (!form->flag[0] && form->width > (hexlen + form->zero))
		form->sp_beg = form->width - (hexlen + form->zero);
	else
	{
		ft_flag_sort(form);
		if (form->flag[1] == HASH)
		{
			form->hsign = 1;
			form->width -= 2;
		}
		if (form->width > hexlen + form->zero)
		{
			if (form->flag[0] == HYPHEN)
				form->sp_end = form->width - (hexlen + form->zero);
			else if (form->prec < 0 && form->flag[0] == ZERO)
				form->zero = form->width - (hexlen + form->zero);
			else
				form->sp_beg = form->width - (hexlen + form->zero);
		}
	}
}

static void	ft_flag_sort(t_form *form)
{
	int	flg;

	flg = form->flag[0];
	if (flg == HASH)
	{
		form->flag[0] = form->flag[1];
		form->flag[1] = flg;
	}
}
