/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:01:53 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 19:01:57 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			handle_operator(t_mshell *ms_data, char *input, int *i);
static int	is_three_char_invalid(char c0, char c1, char c2);
static int	is_two_char_invalid(char c0, char c1);
static void	handle_invalid_token(t_mshell *ms, char *input, int *i, int len);
int			op_syntax_invalid(t_mshell *ms, char *input, int *i);

int	handle_operator(t_mshell *ms_data, char *input, int *i)
{
	char	c;

	if (op_syntax_invalid(ms_data, input, i))
		return (-1);
	c = input[*i];
	if (c == '|' && input[*i +1] && input[*i +1] == '|')
		*i += add_token(ms_data, TYPE_OR, "||");
	else if (c == '|')
		*i += add_token(ms_data, TYPE_PIPE, "|");
	else if (c == '&' && input[*i +1] && input[*i +1] == '&')
		*i += add_token(ms_data, TYPE_AND, "&&");
	else if (c == '>' && input[*i +1] && input[*i +1] == '>')
		*i += add_token(ms_data, TYPE_REDIR_APP, ">>");
	else if (c == '>')
		*i += add_token(ms_data, TYPE_REDIR_OUT, ">");
	else if (c == '<' && input[*i +1] && input[*i +1] == '<')
		*i += add_token(ms_data, TYPE_REDIR_HDC, "<<");
	else if (c == '<')
		*i += add_token(ms_data, TYPE_REDIR_IN, "<");
	else if (c == '(')
		*i += add_token(ms_data, TYPE_PAREN_OPEN, "(");
	else if (c == ')')
		*i += add_token(ms_data, TYPE_PAREN_CLOSE, ")");
	return (0);
}

static int	is_three_char_invalid(char c0, char c1, char c2)
{
	return ((c0 == '|' && c1 == '|' && c2 == '|')
		|| (c0 == '&' && c1 == '&' && c2 == '&')
		|| (c0 == '>' && c1 == '>' && c2 == '>')
		|| (c0 == '<' && c1 == '<' && c2 == '<')
		|| (c0 == '(' && c1 == '(' && c2 == '('));
}

static int	is_two_char_invalid(char c0, char c1)
{
	return ((c0 == '|' && c1 && ft_strchr("><&", c1))
		|| (c0 == '&' && c1 && ft_strchr("><|", c1))
		|| (c0 == '>' && c1 && ft_strchr("<|&", c1))
		|| (c0 == '<' && c1 && ft_strchr(">|&", c1)));
		//|| (c0 == '(' && c1 && (c1 == '(' || c1 == ')')));
}

static void	handle_invalid_token(t_mshell *ms, char *input, int *i, int len)
{
	char	*invalid;
	int		flag;

	invalid = ft_substr(input, *i, len);
	if (!invalid)
		err_exit(ERR_MSG_MEM, 1);
	add_token(ms, TYPE_SYNTAX_INVALID, invalid);
	flag = OP_SYNTAX_INVALID;
	err_syntax(invalid, &flag);
	free(invalid);
	free_token_and_reset(&ms->tokens);
	*i = ft_strlen(input);
}

int	op_syntax_invalid(t_mshell *ms, char *input, int *i)
{
	char	c[3];
	int		len;

	c[0] = input[*i];
	c[1] = '\0';
	c[2] = '\0';
	if (*i + 1 < (int)ft_strlen(input))
		c[1] = input[*i + 1];
	if (*i + 2 < (int)ft_strlen(input))
		c[2] = input[*i + 2];
	len = 0;
	if (is_three_char_invalid(c[0], c[1], c[2]))
		len = 3;
	else if (is_two_char_invalid(c[0], c[1]))
		len = 2;
	else if (c[0] == '&' && c[1] != '&')
		len = 1;
	if (!len)
		return (0);
	handle_invalid_token(ms, input, i, len);
	return (1);
}
