/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:33:15 by ********          #+#    #+#             */
/*   Updated: 2025/04/02 17:12:31 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

t_env	*search_env_name(t_env *env, char *name)
{
	if (!env)
		return (NULL);
	if (!ft_strncmp(env->key, name, ft_strlen(name) + 1))
		return (env);
	return (search_env_name(env->next, name));
}

char	*get_env_val(t_env *env, char *name)
{
	t_env	*node;

	node = search_env_name(env, name);
	if (node)
		return (node->value);
	return (NULL);
}

int	set_env_val(t_env *env, char *name, char *val)
{
	t_env	*node;

	node = search_env_name(env, name);
	if (!node)
		return (1);
	if (node->value)
		free(node->value);
	node->value = val;
	return (0);
}

void	lst_add_env(t_env **env, t_env *node)
{
	t_env	*tmp;

	if (!*env)
	{
		*env = node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	lst_rm_env(t_env **env, t_env *to_rm)
{
	t_env	*tmp;

	if (*env == to_rm)
	{
		*env = (*env)->next;
		free(to_rm);
		return ;
	}
	tmp = *env;
	while (tmp->next)
	{
		if (tmp->next == to_rm)
		{
			tmp->next = to_rm->next;
			break ;
		}
		tmp = tmp->next;
	}
	if (to_rm->key)
		free(to_rm->key);
	if (to_rm->value)
		free(to_rm->value);
	free(to_rm);
}
