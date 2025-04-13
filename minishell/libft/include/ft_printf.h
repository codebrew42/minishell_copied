/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:47:44 by ********          #+#    #+#             */
/*   Updated: 2024/10/15 14:04:22 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define FLAGS "-0# +"
# define TYPES "scpiduxX%"
# define HEXBASE_UP "0123456789ABCDEF" 
# define HEXBASE_LOW "0123456789abcdef"

typedef enum e_type
{
	TYPE_s,
	TYPE_c,
	TYPE_p,
	TYPE_i,
	TYPE_d,
	TYPE_u,
	TYPE_x,
	TYPE_X,
	TYPE_PERC
}	t_type;

typedef enum e_flags
{
	NONE,
	HYPHEN,
	ZERO,
	HASH,
	SPACE,
	PLUS
}	t_flags;

typedef struct s_form
{
	int		sp_beg;
	int		sp_end;
	int		zero;
	char	sign;
	int		hsign;
	t_type	type;
	t_flags	flag[2];
	int		flag_count;
	int		width;
	int		prec;
}	t_form;

int			ft_printf(const char *s, ...);
void		ft_parse_str(const char *s, va_list *args, int *outlen);
const char	*ft_parse_format(const char *s, va_list *args, int *outlen);
const char	*ft_format_conditions(const char *s, t_form *form, va_list *args);
void		ft_hub_printtype(va_list *args, t_form *form, int *outlen);
void		ft_pf_str(va_list *args, t_form *form, int *outlen);
void		ft_pf_chr(va_list *args, t_form *form, int *outlen);
void		ft_pf_int(va_list *args, t_form *form, int *outlen);
void		ft_pf_uin(va_list *args, t_form *form, int *outlen);
void		ft_pf_hex(va_list *args, t_form *form, int *outlen);
void		ft_pf_ptr(va_list *args, t_form *form, int *outlen);
void		ft_put_hexform(t_form *form, unsigned long n);
void		ft_put_strform(char *str, t_form *form, int slen);
void		ft_put_intform(long n, t_form *form);
int			ft_count_intlen(unsigned int n);
int			ft_hexlen(unsigned long n);

#endif
