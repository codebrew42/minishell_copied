/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hub_printtype.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:50:48 by ********          #+#    #+#             */
/*   Updated: 2024/05/27 19:01:16 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hub_printtype(va_list *args, t_form *form, int *outlen)
{
	if (form->type == TYPE_s)
		ft_pf_str(args, form, outlen);
	else if (form->type == TYPE_c)
		ft_pf_chr(args, form, outlen);
	else if (form->type == TYPE_i || form->type == TYPE_d)
		ft_pf_int(args, form, outlen);
	else if (form->type == TYPE_u)
		ft_pf_uin(args, form, outlen);
	else if (form->type == TYPE_x || form->type == TYPE_X)
		ft_pf_hex(args, form, outlen);
	else if (form->type == TYPE_p)
		ft_pf_ptr(args, form, outlen);
	else if (form->type == TYPE_PERC)
	{
		write(1, "%", 1);
		*outlen += 1;
	}
}
