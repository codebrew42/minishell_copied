/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_intform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:15:45 by ********          #+#    #+#             */
/*   Updated: 2024/05/29 21:16:22 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_intform(long n, t_form *form)
{
	while (form->sp_beg--)
		write(1, " ", 1);
	if (form->sign)
		ft_putchar_fd(form->sign, 1);
	while (form->zero--)
		write(1, "0", 1);
	if (n || form->prec)
		ft_putnbr_fd(n, 1);
	while (form->sp_end--)
		ft_putchar_fd(' ', 1);
}
