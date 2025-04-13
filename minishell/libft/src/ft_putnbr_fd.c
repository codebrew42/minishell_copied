/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:04:06 by ********          #+#    #+#             */
/*   Updated: 2024/05/06 15:49:20 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putdigits(long n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	ft_putdigits(nb, fd);
}

static void	ft_putdigits(long n, int fd)
{
	char	c;

	if (n == 0)
		return ;
	ft_putdigits(n / 10, fd);
	c = n % 10 + 48;
	write(fd, &c, 1);
}
