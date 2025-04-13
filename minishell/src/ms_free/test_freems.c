#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_mshell	*data;

	if (!ac && !av)
		return (1);
	init_mshell(&data, envp);
	data->tokens = calloc(1, sizeof(t_token));
	data->tokens->next = calloc(1, sizeof(t_token));
	free_mshell(data);
	return (0); 
}
