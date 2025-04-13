/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:43:39 by ********          #+#    #+#             */
/*   Updated: 2025/02/27 18:46:49 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	init_data();
	get_input();
	free_data();
	return (0);
}

void	get_input()
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
		heredoc();
		executor();
		free(input); //still memory leak with readline, but the subject says ok...
	}
}
