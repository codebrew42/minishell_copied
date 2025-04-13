/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:38:38 by ********          #+#    #+#             */
/*   Updated: 2024/05/08 22:58:43 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(long n);
static void	ft_conv_int(long n, char *result, int idx);

char	*ft_itoa(int n)
{
	long	cp;
	char	*result;
	int		minus;
	int		nlen;

	if (n == 0)
		return (ft_strdup("0"));
	cp = n;
	minus = 0;
	if (n < 0)
	{
		minus++;
		cp *= -1;
	}
	nlen = ft_numlen(cp);
	result = malloc(nlen + minus + 1);
	if (!result)
		return (NULL);
	if (minus)
		result[0] = '-';
	result[nlen + minus] = '\0';
	ft_conv_int(cp, result, nlen + minus - 1);
	return (result);
}

static void	ft_conv_int(long n, char *result, int idx)
{
	if (!n)
		return ;
	result[idx] = n % 10 + 48;
	ft_conv_int(n / 10, result, --idx);
}

static int	ft_numlen(long n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}
