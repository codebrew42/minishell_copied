/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:26:20 by ********          #+#    #+#             */
/*   Updated: 2024/05/08 21:02:44 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_free(char **str, int n);
static unsigned int	ft_count_words(char const *s, char c);
static char			**ft_maketable(char **result, char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!result)
		return (NULL);
	result = ft_maketable(result, s, c);
	if (!result)
		return (NULL);
	return (result);
}

static char	**ft_maketable(char **result, char const *s, char c)
{
	int		len;
	int		idx;

	idx = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		len = 0;
		while (s[len] != c && s[len])
			len++;
		result[idx] = ft_substr(s, 0, len);
		if (!result[idx])
		{
			ft_free(result, idx);
			return (NULL);
		}
		idx++;
		s += len;
	}
	result[idx] = 0;
	return (result);
}

static unsigned int	ft_count_words(char const *s, char c)
{
	unsigned int	n;

	n = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			n++;
		while (*s != c && *s)
			s++;
	}
	return (n);
}

static void	ft_free(char **str, int n)
{
	while (n-- >= 0)
		free(str[n]);
	free(str);
}
