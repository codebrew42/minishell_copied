/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:59:31 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 18:59:31 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_ast	*tk_to_ast(t_token **cur_tk, t_ast **cur_ast, t_ast **ast_root);
int				parser(t_token **tokens, t_ast **ast_root);
t_ast			*save_args_redirs(t_token **tokens, t_ast **cur, t_ast **root);
t_ast			*save_args(t_token **tokens, t_ast **cur, t_ast **root);
t_ast			*save_single_arg(t_token **tokens, t_ast **cur, t_ast **root);

/*
t_ast	*save_type(t_token **tokens, t_ast **current, t_ast **root)
{
	t_ast	*node;

	node = create_ast_node((*tokens)->type);
	if (!node)
		return (NULL);
	node->type = (*tokens)->type;
	node->args = NULL;
	save_to_position(root, current, node);
	return (node);
}
	
static t_ast	*tk_to_ast(t_token **cur_tk, t_ast **cur_ast, t_ast **ast_root)
{
	while (*cur_tk)
	{
		if (is_paren_type((*cur_tk)->type) || is_op_type((*cur_tk)->type))
			*cur_ast = save_type(cur_tk, cur_ast, ast_root);
		else if (has_embedded_redirs(*cur_tk))
			*cur_ast = save_args_redirs(cur_tk, cur_ast, ast_root);
		else if (is_redir_not_hdc_type((*cur_tk)->type))
			*cur_ast = save_single_arg(cur_tk, cur_ast, ast_root);
		else
			*cur_ast = save_args(cur_tk, cur_ast, ast_root);
		if (!*cur_ast)
			return (NULL);
		*cur_tk = (*cur_tk)->next;
	}
	return (*cur_ast);
}*/

static t_ast	*tk_to_ast(t_token **cur_tk, t_ast **cur_ast, t_ast **ast_root)
{
	t_ast	*node;

	while (*cur_tk)
	{
		if (is_paren_type((*cur_tk)->type) || is_op_type((*cur_tk)->type))
		{
			node = create_ast_node((*cur_tk)->type);
			if (!node)
				return (NULL);
			node->args = NULL;
			save_to_position(ast_root, cur_ast, node);
			*cur_ast = node;
		}
		else if (has_embedded_redirs(*cur_tk))
			*cur_ast = save_args_redirs(cur_tk, cur_ast, ast_root);
		else if (is_redir_not_hdc_type((*cur_tk)->type))
			*cur_ast = save_single_arg(cur_tk, cur_ast, ast_root);
		else
			*cur_ast = save_args(cur_tk, cur_ast, ast_root);
		if (!*cur_ast)
			return (NULL);
		*cur_tk = (*cur_tk)->next;
	}
	return (*cur_ast);
}

int	parser(t_token **tokens, t_ast **ast_root)
{
	t_token		*cur_tk;
	t_ast		*cur_ast;
	t_token		*head;

	if (!tokens || !*tokens || !ast_root)
		return (0);
	head = *tokens;
	cur_tk = head;
	cur_ast = NULL;
	*ast_root = NULL;
	if (!tk_to_ast(&cur_tk, &cur_ast, ast_root))
		return (*tokens = head, 0);
	*tokens = head;
	return (validate_ast(ast_root, tokens, head));
}

t_ast	*save_args_redirs(t_token **tokens, t_ast **cur, t_ast **root)
{
	t_ast	*cmd_node;
	t_ast	*next_node;
	t_token	*start;

	if (!tokens || !*tokens)
		return (NULL);
	start = *tokens;
	cmd_node = create_ast_node(TYPE_CMD);
	if (!cmd_node)
		return (NULL);
	save_to_position(root, cur, cmd_node);
	if (!save_args_skip_redir(tokens, cmd_node, start))
		return (free_ast(cmd_node), NULL);
	next_node = cmd_node;
	if (!process_redirections(start, &next_node))
		return (free_ast(cmd_node), NULL);
	return (next_node);
}

t_ast	*save_single_arg(t_token **tokens, t_ast **cur, t_ast **root)
{
	t_ast	*node;

	node = create_ast_node((*tokens)->type);
	if (!node)
		return (NULL);
	if (is_redirection_type((*tokens)->type) && (*tokens)->next
		&& (*tokens)->next->type == TYPE_TMP_WORD)
	{
		node->args = malloc(sizeof(char *) * 2);
		if (!node->args)
			return (free(node), NULL);
		node->args[0] = ft_strdup((*tokens)->next->value);
		if (!node->args[0])
		{
			free(node->args);
			return (free(node), NULL);
		}
		node->args[1] = NULL;
		*tokens = (*tokens)->next;
	}
	save_to_position(root, cur, node);
	return (node);
}

t_ast	*save_args(t_token **tokens, t_ast **cur, t_ast **root)
{
	t_ast	*node;

	if (!tokens || !*tokens)
		return (NULL);
	if ((*tokens)->type == TYPE_REDIR_HDC)
	{
		if (!(*tokens)->next || (*tokens)->next->type != TYPE_TMP_WORD)
		{
			err_syntax("syntax error near unexpected token `newline'\n", NULL);
			return (NULL);
		}
		node = create_ast_node(TYPE_REDIR_HDC);
	}
	else
		node = create_ast_node(TYPE_CMD);
	if (!node)
		return (NULL);
	node->args = collect_cmd_args(tokens);
	if (!node->args)
	{
		free_ast(node);
		return (NULL);
	}
	save_to_position(root, cur, node);
	return (node);
}
