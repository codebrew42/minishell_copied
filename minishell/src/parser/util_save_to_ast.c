/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_save_to_ast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:59:44 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 18:59:45 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			save_to_position(t_ast **root, t_ast **current, t_ast *node);
t_ast			*create_ast_node(t_type type);
static int		count_cmd_args(t_token *tokens);
static char		*remove_quotes(char *value);
char			**collect_cmd_args(t_token **tokens);

void	save_to_position(t_ast **root, t_ast **current, t_ast *node)
{
	if (!(*root))
		*root = node;
	else if (*current)
		(*current)->right = node;
}

t_ast	*create_ast_node(t_type type)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static int	count_cmd_args(t_token *tokens)
{
	int		arg_count;
	t_token	*tmp;

	arg_count = 0;
	tmp = tokens;
	if (tmp && tmp->type == TYPE_REDIR_HDC)
		tmp = tmp->next;
	while (tmp && (tmp->type == TYPE_TMP_WORD))
	{
		arg_count++;
		tmp = tmp->next;
	}
	return (arg_count);
}

static char	*remove_quotes(char *value)
{
	int		i;
	int		j;
	char	*result;

	if (!value)
		return (NULL);
	if (value[0] == '\0')
		return (ft_strdup(""));
	if (ft_strlen(value) < 2)
		return (ft_strdup(value));
	if ((value[0] == '\'' && value[ft_strlen(value) - 1] == '\'')
		|| (value[0] == '"' && value[ft_strlen(value) - 1] == '"'))
	{
		result = ft_calloc(ft_strlen(value), sizeof(char));
		if (!result)
			return (NULL);
		i = 1;
		j = 0;
		while (value[i] && i < (int)ft_strlen(value) - 1)
			result[j++] = value[i++];
		result[j] = '\0';
		return (result);
	}
	else
		return (ft_strdup(value));
}

char	**collect_cmd_args(t_token **tokens)
{
	char	**args;
	int		arg_count;
	int		i;
	char	*processed;

	arg_count = count_cmd_args(*tokens);
	args = ft_calloc(arg_count + 1, sizeof(char *));
	if (!args)
		return (NULL);
	if ((*tokens)->type == TYPE_REDIR_HDC)
		*tokens = (*tokens)->next;
	i = 0;
	while (i < arg_count && *tokens && (*tokens)->type == TYPE_TMP_WORD)
	{
		processed = remove_quotes((*tokens)->value);
		args[i] = processed;
		if (!args[i])
			return (free_strarr(args), NULL);
		i++;
		if (i < arg_count)
			*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	return (args);
}
