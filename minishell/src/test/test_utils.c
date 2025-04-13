#include "minishell.h"
#include "executor.h"
#include "test_ms.h"

void	lst_add_ast(t_ast **ast, t_type t, char *argstr)
{
	char	**args;

	args = NULL;
	if (argstr)
	{
		args = ft_split(argstr, ' ');
		if (!args)
			err_exit(NULL,0);
	}
	set_ast(ast, t, &args);
}

void	set_ast(t_ast **ast, t_type t, char ***args)
{
	*ast = ft_calloc(1, sizeof(t_ast));
	if (!*ast)
		err_exit(NULL, 0);
	(*ast)->type = t;
	(*ast)->args = *args;
	return ;
}

int	find_print_env(t_env *env, char *name)
{
	t_env	*node;

	node = NULL;
	node = search_env_name(env, name);
	if (node)
	{
		printf("key: %s\nvalue: %s\n", node->key, node->value);
		return (0); 
	}
	return (1);
}

void	testprint_ast(t_ast *ast)
{
	char	**tmp;

	if (!ast)
		return ;
	puts("AST");
	printf("\ttype: %d\n", ast->type);
	printf("\targs:\n");
	tmp = ast->args;
	while (tmp && *tmp)
	{
		printf("\t\t%s\n", *tmp);
		tmp++;
	}
	puts("\n*****\n");
	testprint_ast(ast->right);
}

void	testprint_cmds(t_cmd *cmd)
{
	if (!cmd)
		return ;
	char	**tmp;

	tmp = cmd->args;
	printf("args:");
	while (*tmp)
	{
		printf("\t%s\n", *tmp);
		tmp++;
	}
	if (cmd->bi)
		printf("bi: %d\n", cmd->bi);
	if (cmd->op)
		printf("op: %d\n", cmd->op);
	if (cmd->type_rdct[0])
		printf("rd in: %d\nfile_path: %s\n", cmd->type_rdct[0], cmd->file_path[0]);
	if (cmd->type_rdct[1])
		printf("rd out: %d\nfile_path: %s\n", cmd->type_rdct[1], cmd->file_path[1]);
	if (cmd->paren[0])
		printf("(:  %d\n", cmd->paren[0]);
	if (cmd->paren[1])
		printf("): %d\n", cmd->paren[1]);
	
	puts("\n*****\n");
	testprint_cmds(cmd->next);
}
