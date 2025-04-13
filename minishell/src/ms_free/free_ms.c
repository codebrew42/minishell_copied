/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:04:50 by ********          #+#    #+#             */
/*   Updated: 2025/03/29 14:04:39 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

void	free_mshell(t_mshell *data);
void	free_ast(t_ast *ast);
void	free_tkn(t_token *t);
void	free_env(t_env *env);
void	free_hdc(t_heredoc *hdc);

void	free_mshell(t_mshell *data)
{
	if (!data)
		return ;
	clear_history();
	if (data->tokens)
		free_token_and_reset(&data->tokens);
	if (data->ast_root)
		free_ast(data->ast_root);
	if (data->env_var)
		free_env(data->env_var);
	if (data->path)
		free_matrix(data->path, 0);
	if (data->hdc)
		free_hdc(data->hdc);
	free(data);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	free_ast(ast->right);
	if (ast->args)
		free_matrix(ast->args, 0);
	free(ast);
}

void	free_tkn(t_token *t)
{
	if (!t)
		return ;
	free_tkn(t->next);
	if (t->value)
		free(t->value);
	free(t);
}

void	free_env(t_env *env)
{
	if (!env)
		return ;
	free_env(env->next);
	free(env->key);
	free(env->value);
	free(env);
}

void	free_hdc(t_heredoc *hdc)
{
	if (!hdc)
		return ;
	free_hdc(hdc->next);
	free(hdc->filename);
	free(hdc);
}
