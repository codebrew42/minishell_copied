/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:48:20 by ********          #+#    #+#             */
/*   Updated: 2025/03/22 21:44:18 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	set_env(t_env *env, char **args, char ***path);
static void	add_env(t_env *env, t_env *new);
static int	parse_env_arg(char *arg, t_env *node);
static int	set_new_pathlist(char ***path, char *str);

int	ms_export(t_mshell *data, char **args)
{
	if (!args[1])
		return (ms_env(data->env_var), 0);
	return (set_env(data->env_var, args + 1, &data->path));
}

static int	set_env(t_env *env, char **args, char ***path)
{
	t_env	*new;

	if (!*args)
		return (0);
	if (!**args)
		return (err_msg(ERR_IDF, args[0]), set_env(env, args + 1, path), 1);
	else if (*args[0] == '=')
		return (err_msg(ERR_IDF, args[0]), set_env(env, args + 1, path), 1);
	else
	{
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			return (ERR);
		if (parse_env_arg(*args, new) == ERR)
			return (free(new), ERR);
		if (!strncmp(new->key, "PATH", 5))
			set_new_pathlist(path, new->value);
		add_env(env, new);
	}
	return (set_env(env, args + 1, path));
}

static void	add_env(t_env *env, t_env *new)
{
	t_env	*node;

	node = NULL;
	node = search_env_name(env, new->key);
	if (node)
	{
		if (node->value)
			free(node->value);
		node->value = new->value;
		free(new->key);
		free(new);
	}
	else
		lst_add_env(&env, new);
}

static int	parse_env_arg(char *arg, t_env *node)
{
	char	*ecual;

	ecual = ft_strchr(arg, '=');
	if (ecual)
		node->key = ft_substr(arg, 0, ecual - arg);
	else
		node->key = ft_strdup(arg);
	if (!node->key)
		return (ERR);
	if (ecual)
	{
		node->value = ft_strdup(ecual + 1);
		if (!node->value)
			return (free(node->key), ERR);
	}
	return (0);
}

static int	set_new_pathlist(char ***path, char *str)
{
	free_matrix(*path, 0);
	*path = ft_split(str, ':');
	if (!*path)
		return (ERR);
	return (0);
}
