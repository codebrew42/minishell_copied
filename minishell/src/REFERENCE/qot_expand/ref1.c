
void custom_remove_quotes(char *str)
{
	int i = 0;
	int j = 0;
	int in_single_quotes = 0;
	int in_double_quotes = 0;
	
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			i++;
			continue;
		}
		else if (str[i] == '"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			i++;
			continue;
		}
		str[j++] = str[i++];
	}
	str[j] = '\0';
}

void process_ast_nodes(t_ast *ast, char **envp)
{
	if (!ast)
		return;
	
	if (ast->type == TYPE_CMD)
	{
		for (int i = 0; ast->args && ast->args[i]; i++)
		{
			char *processed = strdup(ast->args[i]);
			if (!processed)
				err_exit("Memory allocation failed", 1);
			if (should_expand_vars(processed))
			{
				char *expanded = simulate_bash_expansion(processed);
				free(processed);
				processed = expanded;
			}
			custom_remove_quotes(processed); //fix rm quotes
			free(ast->args[i]);
			ast->args[i] = processed;
		}
	}
	(void)envp;
	//process_ast_nodes(ast->left, envp);
	//process_ast_nodes(ast->right, envp);
}