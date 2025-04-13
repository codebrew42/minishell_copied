/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:57:49 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 18:57:50 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*create_env_node(char *key, char *value);
static t_env	*save_to_new_env_node(char *str, char *equals_pos);
static void		parse_env_var(t_mshell *ms_data, char **envp);
static void		parse_path(t_mshell *ms_data);
int				init_mshell(t_mshell **ms_data, char **envp);

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

static t_env	*save_to_new_env_node(char *str, char *equals_pos)
{
	char	*key;
	char	*val;
	t_env	*tmp;
	int		key_len;

	key_len = equals_pos - str;
	key = malloc(key_len + 1);
	if (!key)
	{
		err_exit(NULL, 0);
		return (NULL);
	}
	ft_memmove(key, str, key_len);
	key[key_len] = '\0';
	val = equals_pos + 1;
	val = ft_strdup(val);
	tmp = create_env_node(key, val);
	free(key);
	free(val);
	return (tmp);
}

static void	parse_env_var(t_mshell *ms_data, char **envp)
{
	int		i;
	t_env	*cur;
	t_env	*tmp;
	char	*equals_pos;

	ms_data->env_var = NULL;
	i = 0;
	while (envp[i])
	{
		equals_pos = ft_strchr(envp[i], '=');
		if (equals_pos)
		{
			tmp = save_to_new_env_node(envp[i], equals_pos);
			if (!ms_data->env_var)
				ms_data->env_var = tmp;
			else
			{
				cur = ms_data->env_var;
				while (cur->next)
					cur = cur->next;
				cur->next = tmp;
			}
		}
		i++;
	}
}

static void	parse_path(t_mshell *ms_data)
{
	t_env	*current;

	ms_data->path = NULL;
	current = ms_data->env_var;
	while (current)
	{
		if (ft_strncmp(current->key, "PATH", ft_strlen(current->key)) == 0)
		{
			ms_data->path = ft_split(current->value, ':');
			return ;
		}
		current = current->next;
	}
}

int	init_mshell(t_mshell **ms_data, char **envp)
{
	*ms_data = (t_mshell *)malloc(sizeof(t_mshell));
	if (!*ms_data)
		err_exit(NULL, 0);
	(*ms_data)->tokens = NULL;
	(*ms_data)->ast_root = NULL;
	(*ms_data)->envp = envp;
	(*ms_data)->hdc = NULL;
	(*ms_data)->exit_requested = 0;
	(*ms_data)->dol_questn = 0;
	parse_env_var(*ms_data, envp);
	parse_path(*ms_data);
	return (0);
}
