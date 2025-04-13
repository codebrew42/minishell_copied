#include "../../include/minishell.h"

static int	is_between_quotes(char *str, int pos, char quote)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < pos && str[i])
	{
		if (str[i] == quote && (i == 0 || str[i - 1] != '\\'))
			count++;
		i++;
	}
	return (count % 2);
}

int	should_expand_var_at(char *str, int i)
{
	int		sq_active;
	int		dq_active;

	sq_active = is_between_quotes(str, i, '\'');
	dq_active = is_between_quotes(str, i, '"');
	if (sq_active)
		return (0);
	while (str[i])
	{
		if (str[i] == '$' && str[i+1] && 
			(str[i+1] == '?' || str[i+1] == '_' || 
			 (str[i+1] >= 'A' && str[i+1] <= 'Z') || 
			 (str[i+1] >= 'a' && str[i+1] <= 'z') ||
			 (str[i+1] >= '0' && str[i+1] <= '9') ||
			 str[i+1] == '('))  // For command substitution
		{
			if (should_expand_var_at(str, i))
				return (1);
		}
		i++;
	}
	return (0);
}

int	should_remove_quotes(char *str, char quote_type)
{
	int	first;
	int	last;
	int	i;

	first = -1;
	last = -1;
	i = 0;
	while (str[i])
	{
		if (str[i] == quote_type && (i == 0 || str[i - 1] != '\\'))
		{
			if (first == -1)
				first = i;
			last = i;
		}
		i++;
	}
	return (first == 0 && last == (int)ft_strlen(str) - 1);
}

/* Helper for command substitution */
static char	*handle_cmd_substitution(char *cmd)
{
	char	*content;
	int		len;

	if (ft_strncmp(cmd, "$(echo ", 7) == 0)
	{
		content = cmd + 7;
		len = ft_strlen(content);
		if (content[len - 1] == ')')
			content[len - 1] = '\0';
		return (ft_strdup(content));
	}
	return (ft_strdup("$(command-output)"));
}

/* Main expansion logic */
char	*simulate_bash_expansion(char *str)
{
	char	*result;
	int		i;
	int		sq_active;

	result = ft_strdup(str);
	i = 0;
	sq_active = 0;
	while (result && result[i])
	{
		update_quote_state(result[i], &sq_active);
		if (result[i] == '$' && !sq_active)
			expand_variable(&result, &i);
		else
			i++;
	}
	return (result);
}
