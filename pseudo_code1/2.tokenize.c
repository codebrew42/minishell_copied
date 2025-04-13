#include "minishell.h"


int	count_tokens(char *list)
{
	int		i;
	int		nbr_of_tokens;
	int		len;

	if (!list)
		return (handle_errors(1, NULL, NULL, 0));
	i = 0;
	len = ft_strlen(list);
	nbr_of_tokens = 0;
	while (i < len)
	{
		while (list[i] == ' ')
			i++;
		if ((list[i] == '<' && list[i + 1] == '<') || (list[i] == '>' && list[i + 1] == '>'))
		{
			nbr_of_tokens++;
			i += 2;
		}
		else if (list[i] == '|' || list[i] == '<' || list[i] == '>')
		{
			nbr_of_tokens++;
			i++;
		}
		else if (list[i] == '$')
		{
			nbr_of_tokens++;
			i++;
		}
		else
			i++;
	}
}

int	save_token()
{
	//save type: WORD, PIPE, RED_IN, RED_OUT, RED_APP, RED_HEREDOC, ENV_VAR

	//create a token (linked list)
	//save to the token

}


//if one part fails, free 
int	tokenize_input(t_shell *s, char *l)
{
	int		i;
	int		nbr_of_tokens;
	int		len;

	if (!l)
		return (handle_errors(1, NULL, NULL, 0));
	i = 0;
	if (all_quotes_balanced(l))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", STDERR_FILENO);
		return (2);
	}
	while (l[i])
	{
		skip_spaces(l, i); //(1)multiple -> single (2) inside quotes, maintain //ouside_outer_quotes
		if (!l[i])
			break ;
		//handle operator : |<>
		if (is_operater(l[i]))
			save_token(l, &i, OPERATOR);
		//handle quotes
		else if (is_quote(l[i])) //just handle outer quotes
			save_token(l, &i, QUOTE);
		//option : always regard a char
		else if (is_escape(l[i]))
			save_token(l, &i, ESCAPE);; //check: needed?
		//handle regular words
		else 
			save_token(l, &i, WORD);
	}

}

