/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:46:21 by ********          #+#    #+#             */
/*   Updated: 2024/05/29 21:01:03 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_str(va_list *args, t_form *form, int *outlen)
{
	char	*str;
	int		len;

	str = va_arg(*args, char *);
	if (!str)
	{
		if (form->prec >= 0 && form->prec < 6)
			str = "";
		else
			str = "(null)";
	}
	len = ft_strlen(str);
	if (0 <= form->prec && form->prec < len)
		len = form->prec;
	if (form->width > len)
	{
		if (form->flag[0] == HYPHEN)
			form->sp_end = form->width - len;
		else
			form->sp_beg = form->width - len;
	}
	*outlen += (len + form->sp_beg + form->sp_end);
	ft_put_strform(str, form, len);
}

void	ft_put_strform(char *str, t_form *form, int slen)
{
	int	i;

	while (form->sp_beg--)
		ft_putchar_fd(' ', 1);
	i = 0;
	while (i < slen)
		ft_putchar_fd(str[i++], 1);
	while (form->sp_end--)
		ft_putchar_fd(' ', 1);
}
