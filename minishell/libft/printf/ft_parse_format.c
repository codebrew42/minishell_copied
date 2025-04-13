/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:02:55 by ********          #+#    #+#             */
/*   Updated: 2024/05/29 21:44:15 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_struct_reset(t_form *form);

const char	*ft_parse_format(const char *s, va_list *args, int *outlen)
{
	t_form	*form;

	form = malloc(sizeof(t_form));
	if (!form)
		return (NULL);
	ft_struct_reset(form);
	s = ft_format_conditions(s, form, args);
	if (!s)
		return (free(form), NULL);
	ft_hub_printtype(args, form, outlen);
	return (free(form), s);
}

static void	ft_struct_reset(t_form *form)
{
	ft_bzero(form, sizeof(t_form));
	form->width = -1;
	form->prec = -1;
}
