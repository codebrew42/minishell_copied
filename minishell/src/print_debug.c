#include "minishell.h"

void	print_arr(char **str)
{
	int i = 0;
	printf("printing path starts...\n");
	while (str[i])
	{
		printf("str[%d]: %s\n", i, str[i]);
		i++;
	}
	printf("printing path ends...\n");
}


void	print_token(t_mshell *ms_data)
{
	t_token	*token;

	token = ms_data->tokens;
	printf(" * * * print_token starts * * * \n");
	while (token)
	{
		printf("token's type: %s\n", get_type_str(token->type));
		printf("token's value: %s\n", token->value);
		token = token->next;
	}
	printf(" * * * print_token ends * * * \n");
}

char	*get_type_str(t_type type)
{
	if (type == TYPE_SYNTAX_INVALID)
		return ("TYPE_SYNTAX_INVALID");
	else if (type == TYPE_TMP_WORD)
		return ("TYPE_TMP_WORD");
	else if (type == TYPE_CMD)
		return ("TYPE_CMD");
	else if (type == TYPE_PIPE)
		return ("TYPE_PIPE");
	else if (type == TYPE_OR)
		return ("TYPE_OR");
	else if (type == TYPE_AND)
		return ("TYPE_AND");
	else if (type == TYPE_REDIR_IN)
		return ("TYPE_REDIR_IN");
	else if (type == TYPE_REDIR_OUT)
		return ("TYPE_REDIR_OUT");
	else if (type == TYPE_REDIR_APP)
		return ("TYPE_REDIR_APP");
	else if (type == TYPE_REDIR_HDC)
		return ("TYPE_REDIR_HDC");
	else if (type == TYPE_PAREN_OPEN)
		return ("TYPE_PAREN_OPEN");
	else if (type == TYPE_PAREN_CLOSE)
		return ("TYPE_PAREN_CLOSE");
	else if (type == TYPE_ENV_QUESTION)
		return ("TYPE_ENV_QUESTION");
	else if (type == TYPE_ENV_VAR)
		return ("TYPE_ENV_VAR");
	return ("UNKNOWN_TYPE");
}

static void	print_ast_node(t_ast *ast, int node_num)
{
	int	i;

	printf("Node %d: [%s]\n", node_num, get_type_str(ast->type));
	printf("  Args: ");
	if (ast->args)
	{
		printf("[\n");
		i = 0;
		while (ast->args[i])
		{
			printf("    arg[%d]: '", i);
			int j = 0;
			while (ast->args[i][j])
			{
				printf("%c", ast->args[i][j]);
				j++;
			}
			printf("' (len=%zu, hex=", ft_strlen(ast->args[i]));
			j = 0;
			while (ast->args[i][j])
			{
				printf("%02x ", (unsigned char)ast->args[i][j]);
				j++;
			}
			printf(")\n");
			i++;
		}
		printf("  ]");
	}
	else
		printf("(null args)");
	printf("\n");
	if (ast->right)
		printf("  Next → Node %d [%s]\n", node_num + 1, 
			get_type_str(ast->right->type));
	else
		printf("  Next → (none)\n");
	printf("------------------------\n");
}

void	print_ast(t_mshell *ms_data)
{
	t_ast	*ast;
	int		node_count;

	ast = ms_data->ast_root;
	node_count = 0;
	printf("\n===== AST STRUCTURE =====\n");
	if (!ast)
	{
		printf("(empty)\n");
		printf("=======================\n\n");
		return ;
	}
	while (ast)
	{
		print_ast_node(ast, ++node_count);
		ast = ast->right;
	}
	printf("=======================\n\n");
}

void debug_print_hex(const char *str)
{
	int i = 0;
	printf("String hex dump: ");
	if (!str)
	{
		printf("(NULL)\n");
		return;
	}
	while (str[i])
	{
		printf("%02x ", (unsigned char)str[i]);
		i++;
	}
	printf("\n");
}
