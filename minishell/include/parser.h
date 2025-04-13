/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:53:47 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 18:53:49 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_ast		t_ast;
typedef struct s_mshell		t_mshell;
typedef enum e_type			t_type;

/* parser.c */
int		parser(t_token **tokens, t_ast **ast_root);
t_ast	*save_args(t_token **tokens, t_ast **current, t_ast **root);
t_ast	*save_single_arg(t_token **tokens, t_ast **current, t_ast **root);
t_ast	*save_args_redirs(t_token **tokens, t_ast **current, t_ast **root);
void	free_strarr(char **arr);

/* util_cmd_with_redir.c */
int		has_embedded_redirs(t_token *tokens);
int		save_args_skip_redir(t_token **tokens, t_ast *cmd_node, t_token *start);
int		count_actual_args(t_token *start);
int		process_redirections(t_token *start, t_ast **last_node);
t_ast	*create_redir_node(t_token *redir, t_token *target, t_ast **last_node);

/* validate_ast.c */
int		validate_ast(t_ast **ast, t_token **tokens, t_token *head);
int		validate_nodes_with_arg(t_ast *ast);
int		validate_parentheses_nodes(t_ast *ast);

/* validate_linked_op.c */
int		validate_linked_operators(t_ast *ast);
int		validate_start_end_op(t_ast *ast);

/* util_type_check.c */
int		is_redir_not_hdc_type(t_type type);
int		is_redirection_type(t_type type);
int		is_not_op_or_paren(t_type type);
int		is_op_type(t_type type);
int		is_paren_type(t_type type);

/* util_save_to_ast.c */
void	save_to_position(t_ast **root, t_ast **current, t_ast *node);
t_ast	*create_ast_node(t_type type);
char	**collect_cmd_args(t_token **tokens);
//t_ast	*save_type(t_token **tokens, t_ast **current, t_ast **root);

/* Memory management functions */
void	free_ast(t_ast *node);

#endif
