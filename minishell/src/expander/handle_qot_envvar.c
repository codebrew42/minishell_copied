/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_qot_envvar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:00:20 by jiepark           #+#                    */
/*   Updated: 2025/03/17 19:00:23 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		handle_qot_envvar(t_mshell *ms, t_ast *node);
static char	*process_arg(t_mshell *ms, char *arg);
static char	*process_quotes(char *arg);
static int	is_in_single_quotes(char *str, char *pos);

void	handle_qot_envvar(t_mshell *ms, t_ast *node)
{
	int	i;

	if (!node || !node->args)
		return ;
	if (node->type == TYPE_CMD || is_redirection_type(node->type))
	{
		i = 0;
		while (node->args[i])
		{
			if (needs_processing(node->args[i]))
				node->args[i] = process_arg(ms, node->args[i]);
			i++;
		}
	}
	if (node->right)
		handle_qot_envvar(ms, node->right);
}

static char	*process_arg(t_mshell *ms, char *arg)
{
	char	*processed;
	char	*result;

	if (!arg)
		return (NULL);
	if (ft_strchr(arg, '$') && !is_in_single_quotes(arg, ft_strchr(arg, '$')))
	{
		processed = ev_expander(ms, ft_strdup(arg));
		if (processed)
		{
			free(arg);
			arg = processed;
		}
	}
	result = process_quotes(arg);
	free(arg);
	return (result);
}

static int	is_in_single_quotes(char *str, char *pos)
{
	int		in_single_quotes;
	int		in_double_quotes;
	char	*current;

	in_single_quotes = 0;
	in_double_quotes = 0;
	current = str;
	while (current < pos)
	{
		if (*current == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (*current == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		current++;
	}
	return (in_single_quotes);
}

static char	*process_quotes(char *arg)
{
	char	*result;
	int		i;
	int		j;
	int		in_single_quotes;
	int		in_double_quotes;

	result = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (arg[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else
			result[j++] = arg[i];
		i++;
	}
	return (result);
}
