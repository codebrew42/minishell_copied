/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:54:07 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 18:54:08 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef struct s_mshell	t_mshell;
typedef struct s_token	t_token;

# define UNQUOTED		0
# define SINGLE_QUOTED	1
# define DOUBLE_QUOTED	2

//tokenizer.c
int		tokenizer(t_mshell *ms_data, char *input);
int		valid_quotes(char *str);
int		valid_parentheses(char *str);
int		valid_input(t_mshell *ms_data, char *input);
void	save_token_data(t_mshell *ms, t_token *tmp_token);
int		add_token(t_mshell *ms, int type, char *value);

//handle_operator.c
int		op_syntax_invalid(t_mshell *ms, char *input, int *i);
int		handle_operator(t_mshell *ms_data, char *input, int *i);

//handle_word.c
int		handle_word(t_mshell *ms_data, char *input, int *i);

#endif
