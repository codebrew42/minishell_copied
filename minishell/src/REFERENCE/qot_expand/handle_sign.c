#include "../include/minishell.h"

static char	*process_quotes_escapes(char *str);
static int	get_quote_type(char *str, int len);
static void	process_char(char *str, char *res, int *ij, int qt);
static int	is_special_char(char c);
static void	set_env_token_type(t_token *token, char *processed);

int	remove_quotes(t_mshell *ms, char *input, int *i)
{
	t_token	*token;
	char	*processed;

	(void)input;
	(void)i;
	token = ms->tokens;
	while (token && token->next)
		token = token->next;
	if (!token || token->type != TYPE_TMP_WORD || !token->value)
		return (0);
	processed = process_quotes_escapes(token->value);
	if (!processed)
		return (-1);
	free(token->value);
	token->value = processed;
	
	if (processed[0] == '$')
		set_env_token_type(token, processed);
	else
		token->type = TYPE_CMD;
	
	return (0);
}

static char	*process_quotes_escapes(char *str)
{
	char	*result;
	int		len;
	int		ij[2];
	int		quote_type;

	len = ft_strlen(str);
	result = malloc(len * 2 + 1);
	if (!result)
		return (NULL);
	ij[0] = 0;
	ij[1] = 0;
	quote_type = get_quote_type(str, len);
	if (quote_type)
	{
		ij[0] = 1;
		len--;
	}
	while (ij[0] < len && str[ij[0]])
		process_char(str, result, ij, quote_type);
	result[ij[1]] = '\0';
	return (result);
}

static int	get_quote_type(char *str, int len)
{
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (1);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (2);
	return (0);
}

static void	process_char(char *str, char *res, int *ij, int qt)
{
	if (qt == SINGLE_QUOTED)
		res[ij[1]++] = str[ij[0]++];
	else if (str[ij[0]] == '\\' && (qt == DOUBLE_QUOTED || qt == UNQUOTED))
	{
		if ((qt == DOUBLE_QUOTED && is_special_char(str[ij[0] + 1])) || qt == UNQUOTED)
			ij[0]++;
		if (str[ij[0]])
			res[ij[1]++] = str[ij[0]++];
	}
	else
		res[ij[1]++] = str[ij[0]++];
}

static int	is_special_char(char c)
{
	return (c == '$' || c == '"' || c == '\\' || c == '\n');
}

static void	set_env_token_type(t_token *token, char *processed)
{
	if (processed[1] == '?' && processed[2] == '\0')
	{
		token->type = TYPE_ENV_QUESTION;
		token->value = ft_strndup(processed , 2);
	}
	else if (processed[1] == '\0')
	{
		token->type = TYPE_ENV_VAR;
		token->value = NULL;
	}
	else
	{
		token->type = TYPE_ENV_VAR;
		token->value = ft_strdup(processed);
	}
}

