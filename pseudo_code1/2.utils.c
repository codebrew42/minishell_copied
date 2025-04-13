#include "minishell.h"

/**
 * Tracks quote state while parsing a string
 * @param str The input string to parse
 * @return 1 if all quotes are properly closed, 0 otherwise
 */
int all_quotes_balanced(char *str)
{
	int i;
	char quote_type;
	
	i = 0;
	quote_type = 0;
	while (str[i])
	{
		if (quote_type == 0)
		{
			if (str[i] == '\'' || str[i] == '\"')
				quote_type = str[i];
		}
		else if (str[i] == quote_type) //matched quotes
			quote_type = 0;
		i++;
	}
	return (quote_type == 0); //all quotes are closed
}

int is_quote(char c)
{
	if (c != '\"' && c != '\'')
		return (0);
	return (c);
}

int is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

int is_operator(char *s)
{
	// Check for single operators
	if (*s == '|' && *(s + 1) != '|')
		return (1); // Single pipe
	else if (*s == '<' && *(s + 1) != '<')
		return (1); // Single <
	else if (*s == '>' && *(s + 1) != '>')
		return (1); // Single >
	// Check for double operators
	else if (*s == '<' && *(s + 1) == '<' && *(s + 2) != '<')
		return (1); // <<
	else if (*s == '>' && *(s + 1) == '>' && *(s + 2) != '>')
		return (1); // >>
	// Anything else is not an operator
	return (0);
}

/**
 @brief: skips from str[i]
 @return: number of spaces
*/
int skip_spaces(char *str, int i)
{
	int j;

	j = 0;
	while (is_whitespace(str[i + j]))
		j++;
	return (j);
}