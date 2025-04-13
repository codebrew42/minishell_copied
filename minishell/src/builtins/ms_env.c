/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:35:47 by ********          #+#    #+#             */
/*   Updated: 2025/03/22 21:08:03 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	ms_env(t_env *env)
{
	if (!env)
		return (0);
	// to check: if value of env is NULL (after 'export test' and 'export test=')
	ft_putstr_fd(env->key, 1);
	write(1, "=", 1);
	if (env->value)
		ft_putstr_fd(env->value, 1);
	write(1, "\n", 1);
	return (ms_env(env->next));
}
