#include "minishell.h"
#include "executor.h"
#include "test_ms.h"

void	print_path(char **path)
{
	if (!*path)
		return ;
	printf("%s\n", path[0]);
	print_path(path + 1);
}

void	testprint_args(char **args)
{
	while(*args)
	{
		printf("%s\n", *args);
		args++;
	}
}

void	testprint_lst(t_list *lst)
{
	if (!lst)
	{
		puts("");
		return ;
	}
	printf("%s\n", (char *)lst->content);
	testprint_lst(lst->next);
}
