/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_conditions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:52:28 by ********          #+#    #+#             */
/*   Updated: 2024/05/31 17:26:49 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*ft_check_flag(const char *s, t_form *form);
static const char	*ft_check_width(const char *s, t_form *form, va_list *args);
static const char	*ft_check_prec(const char *s, t_form *form);
static const char	*ft_check_type(const char *s, t_form *form);

const char	*ft_format_conditions(const char *s, t_form *form, va_list *args)
{
	s = ft_check_flag(s, form);
	s = ft_check_width(s, form, args);
	if (!s)
		return (NULL);
	s = ft_check_prec(s, form);
	if (!s)
		return (NULL);
	s = ft_check_type(s, form);
	if (!s)
		return (NULL);
	return (s);
}

static const char	*ft_check_flag(const char *s, t_form *form)
{
	char	*p;
	int		i;

	i = 0;
	p = ft_strchr(FLAGS, *s);
	while (p && i < 2)
	{
		form->flag[i++] = (p - FLAGS) + 1;
		if (i == 2 && form->flag[1] == form->flag[0])
		{
			form->flag[1] = NONE;
			i--;
		}
		s++;
		p = ft_strchr(FLAGS, *s);
	}
	while (p)
	{
		s++;
		p = ft_strchr(FLAGS, *s);
	}
	form->flag_count = i;
	return (s);
}

static const char	*ft_check_width(const char *s, t_form *form, va_list *args)
{
	int		i;
	char	*width_str;

	if (*s == '*')
	{
		form->width = va_arg(*args, int);
		return (++s);
	}
	i = 0;
	while (ft_isdigit(s[i]))
		i++;
	if (i > 0)
	{
		width_str = ft_substr(s, 0, i);
		if (!width_str)
			return (NULL);
		form->width = ft_atoi(width_str);
		free(width_str);
		s += i;
	}
	return (s);
}

static const char	*ft_check_prec(const char *s, t_form *form)
{
	int		i;
	char	*prec_str;

	i = 0;
	if (*s == '.')
	{
		s++;
		if (!ft_isdigit(*s))
			return (form->prec = 0, s);
		while (ft_isdigit(s[i]))
			i++;
		prec_str = ft_substr(s, 0, i);
		if (!prec_str)
			return (NULL);
		form->prec = ft_atoi(prec_str);
		free(prec_str);
		s += i;
	}
	return (s);
}

static const char	*ft_check_type(const char *s, t_form *form)
{
	char	*p;

	p = ft_strchr(TYPES, *s);
	if (p)
	{
		form->type = p - TYPES;
		s++;
	}
	else
		return (NULL);
	return (s);
}
