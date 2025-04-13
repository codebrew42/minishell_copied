/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:43:39 by ********          #+#    #+#             */
/*   Updated: 2025/02/28 17:09:27 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_mshell *ms_data, char **envp);//jin
void	minishell(t_mshell *ms_data); //jin
void	free_mshell_data(t_mshell *ms_data); //kazu
void	handle_signal(); //jin
void	tokenizer(t_mshell *ms_data); //jin
void	parser(t_mshell *ms_data); //jin
heredoc() //kazu
executor() //kazu
builtin() //kazu
exit___() //kazu
free___() //kau


int	main(int ac, char **av, char **envp)
{
	t_mshell	*ms_data;
	
	init_data(&ms_data, envp);
	minishell(ms_data);
	free_mshell_data(ms_data);
	return (0);
}

void	minishell(t_mshell *ms_data)
{
	char	*input;

	while (1)
	{
		handle_signal();
		input = readline("minishell> ");
		if (!input) //break if ctrl + D
			break ;
		if (*input)
			add_history(input);
		tokenizer();
		parser();
		if 
			heredoc();
		executor();
		free(input); //still memory leak with readline, but the subject says ok...
	}
}
