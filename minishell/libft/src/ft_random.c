/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:03:15 by ********          #+#    #+#             */
/*   Updated: 2024/10/15 14:03:34 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_random(int len)
{
	unsigned int	n;

	n = 123456789 + len;
	n ^= n << 13;
	n ^= n >> 17;
	n ^= n << 5;
	n = n % len;
	return (n);
}
