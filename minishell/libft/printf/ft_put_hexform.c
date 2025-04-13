/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hexform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:40:46 by ********          #+#    #+#             */
/*   Updated: 2024/05/29 21:06:57 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex(t_form *form, unsigned long n);

void	ft_put_hexform(t_form *form, unsigned long n)
{
	while (form->sp_beg--)
		ft_putchar_fd(' ', 1);
	if (n && form->hsign)
	{
		if (form->type == TYPE_x || form->type == TYPE_p)
			ft_putstr_fd("0x", 1);
		else
			ft_putstr_fd("0X", 1);
	}
	while (form->zero--)
		ft_putchar_fd('0', 1);
	if (n || form->prec)
	{
		if (!n)
			write(1, "0", 1);
		else
			ft_puthex(form, n);
	}
	while (form->sp_end--)
		ft_putchar_fd(' ', 1);
}

static void	ft_puthex(t_form *form, unsigned long n)
{
	if (!n)
		return ;
	ft_puthex(form, n / 16);
	if (form->type == TYPE_x || form->type == TYPE_p)
		ft_putchar_fd(HEXBASE_LOW[n % 16], 1);
	else
		ft_putchar_fd(HEXBASE_UP[n % 16], 1);
}
