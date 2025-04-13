/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:03:38 by jiepark           #+#    #+#             */
/*   Updated: 2025/04/03 20:50:16 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

sig_atomic_t	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_mshell	*ms_data;

	if (ac != 1 || av[1])
		return (1);
	if (init_mshell(&ms_data, envp))
		return (1);
	minishell(ms_data);
	return (0);
}

static void	process_command(t_mshell *ms_data, char *input)
{
	if (!*input)
		return ;
	add_history(input);
	if (tokenizer(ms_data, input))
		return ;
	if (!parser(&ms_data->tokens, &ms_data->ast_root))
		return ;
//	print_token(ms_data);
	handle_qot_envvar(ms_data, ms_data->ast_root);
	print_ast(ms_data); //db
//	print_ast(ms_data); //db
	g_exit_status = 0;//added
	ms_heredoc(ms_data);
	executor(ms_data);
	g_exit_status = ms_data->dol_questn;
}

void	minishell(t_mshell *ms_data)
{
	char	*input;

	while (!ms_data->exit_requested)
	{
		setup_signals(SIGNAL_MODE_INTERACTIVE);
		if (ms_data->tokens)
		{
			free_token_and_reset(&ms_data->tokens);
			ms_data->tokens = NULL;
		}
		if (ms_data->ast_root)
		{
			free_ast(ms_data->ast_root);
			ms_data->ast_root = NULL;
		}
		//g_exit_status = 0;//rmved:jin
		input = readline("minishell> ");
		if (!input)
			break ;
		process_command(ms_data, input);
		free(input);
	}
	free_mshell(ms_data);
}
