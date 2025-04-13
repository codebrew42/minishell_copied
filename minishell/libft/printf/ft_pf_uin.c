/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_uin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:01:40 by ********          #+#    #+#             */
/*   Updated: 2024/05/29 21:48:08 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_uinform(unsigned int n, t_form *form);
static void	ft_putunb(unsigned int n);

void	ft_pf_uin(va_list *args, t_form *form, int *outlen)
{
	unsigned int	n;
	int				nlen;

	n = va_arg(*args, unsigned int);
	if (!n && !form->prec)
		nlen = 0;
	else
		nlen = ft_count_intlen(n);
	if (form->prec > nlen)
		form->zero = form->prec - nlen;
	if (form->width > (nlen + form->zero))
	{
		if (form->flag[0] == HYPHEN)
			form->sp_end = form->width - (nlen + form->zero);
		else if (nlen && form->flag[0] == ZERO && form->prec < 0)
			form->zero = form->width - (nlen + form->zero);
		else
			form->sp_beg = form->width - (nlen + form->zero);
	}
	*outlen += (nlen + form->sp_beg + form->sp_end + form->zero);
	ft_put_uinform(n, form);
}

int	ft_count_intlen(unsigned int n)
{
	int	nlen;

	if (!n)
		return (1);
	nlen = 0;
	while (n)
	{
		n = n / 10;
		nlen++;
	}
	return (nlen);
}

static void	ft_put_uinform(unsigned int n, t_form *form)
{
	while (form->sp_beg--)
		ft_putchar_fd(' ', 1);
	while (form->zero--)
		ft_putchar_fd('0', 1);
	if (n || form->prec)
	{
		if (!n)
			write(1, "0", 1);
		else
			ft_putunb(n);
	}
	while (form->sp_end--)
		ft_putchar_fd(' ', 1);
}

static void	ft_putunb(unsigned int n)
{
	char	c;

	if (n == 0)
		return ;
	ft_putunb(n / 10);
	c = n % 10 + 48;
	write(1, &c, 1);
}
