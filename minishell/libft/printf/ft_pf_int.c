/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:52:48 by ********          #+#    #+#             */
/*   Updated: 2024/05/29 21:31:41 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_calc_printcond(int nlen, t_form *form);
static void	ft_calc_wid_flags(int nlen, t_form *form);
static void	ft_flag_sort(t_form *form);

void	ft_pf_int(va_list *args, t_form *form, int *outlen)
{
	long	n;
	int		nlen;

	n = va_arg(*args, int);
	if (!n && !form->prec && form->width < 0)
		return ;
	if (n < 0)
	{
		form->sign = '-';
		n *= -1;
	}
	if (!n && !form->prec)
		nlen = 0;
	else
		nlen = ft_count_intlen(n);
	ft_calc_printcond(nlen, form);
	if (form->sign)
		*outlen += 1;
	*outlen += nlen + form->sp_beg + form->zero + form->sp_end;
	ft_put_intform(n, form);
}

static void	ft_calc_printcond(int nlen, t_form *form)
{
	if (form->prec > nlen)
		form->zero = form->prec - nlen;
	if (form->flag[0] == NONE)
	{
		if (form->sign)
			form->width -= 1;
		if (form->width > nlen + form->zero)
			form->sp_beg = form->width - nlen - form->zero;
	}
	else
		ft_calc_wid_flags(nlen, form);
}

static void	ft_calc_wid_flags(int nlen, t_form *form)
{
	ft_flag_sort(form);
	if (form->flag[1])
	{
		if (!form->sign && form->flag[1] == PLUS)
			form->sign = '+';
		else if (!form->sign && form->flag[1] == SPACE)
			form->sign = ' ';
	}
	if (form->sign)
		form->width--;
	if (form->width > (nlen + form->zero))
	{
		if (form->flag[0] == HYPHEN)
			form->sp_end = form->width - nlen - form->zero;
		else if (form->prec < 0 && form->flag[0] == ZERO)
			form->zero = form->width - nlen;
		else
			form->sp_beg = form->width - nlen - form->zero;
	}
}

static void	ft_flag_sort(t_form *form)
{
	int	flg;

	flg = form->flag[0];
	if (flg == PLUS || flg == SPACE)
	{
		form->flag[0] = form->flag[1];
		form->flag[1] = flg;
	}
}
