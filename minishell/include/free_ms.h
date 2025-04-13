/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:51:42 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 18:51:43 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_MS_H
# define FREE_MS_H

typedef struct s_ast		t_ast;
typedef struct s_env		t_env;
typedef struct s_token		t_token;
typedef struct s_heredoc	t_heredoc;
typedef struct s_mshell		t_mshell;

/* free_ms.c */
void	free_mshell(t_mshell *data);
void	free_tkn(t_token *t);
void	free_ast(t_ast *ast);
void	free_env(t_env *env);
void	free_hdc(t_heredoc *hdc);

/* free_ms_utils.c */
void	free_token_and_reset(t_token **t);
void	free_matrix(char **mtx, int idx);
void	free_strarr(char **arr);

#endif
