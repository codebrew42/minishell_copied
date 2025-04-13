/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jiepark <jiepark@student.42berlin.de>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/17 19:00:20 by jiepark		   #+#	#+#			 */
/*   Updated: 2025/04/01 11:00:56 by ********         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(int mode);
void	execution_signal_handler(int sig_nbr);
void	interactive_sigint_handler(int sig);
void	heredoc_sigint_handler(int sig);

void	setup_signals(int mode)
{
	if (mode == SIGNAL_MODE_INTERACTIVE)
	{
		set_terminal_print_off();
		signal(SIGINT, interactive_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIGNAL_MODE_CHILD)
	{
		//set_terminal_print_on();
		set_terminal_print_off();
		signal(SIGINT, cmdproc_signal_handler); 
		signal(SIGQUIT, cmdproc_signal_handler); 
		//signal(SIGINT, SIG_DFL);
		//signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == SIGNAL_MODE_HEREDOC)
	{
		set_terminal_print_off();
		signal(SIGINT, heredoc_sigint_handler); 
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIGNAL_MODE_PARENT_WAITING)
	{
		set_terminal_print_off();
		//set_terminal_print_on();
		signal(SIGINT, execution_signal_handler); 
		signal(SIGQUIT, execution_signal_handler); 
//		signal(SIGINT, SIG_IGN);
		//signal(SIGQUIT, SIG_IGN);
	}
}

void	interactive_sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	g_exit_status = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	close(0);
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);	// Clear input bf
	rl_on_new_line();		// Move cursor to new line
//	rl_done = 1;			// Force readline to return
}

void	execution_signal_handler(int sig_nbr)
{
	g_exit_status = 128 + sig_nbr;
	if (sig_nbr == SIGINT)
		write(STDOUT_FILENO, "\n", 2);
	/*
	if (sig_nbr == SIGINT)
	{
		g_exit_status = 128 + sig_nbr;
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (sig_nbr == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		g_exit_status = 127 + sig_nbr;
	}
	*/
}

void	cmdproc_signal_handler(int sig)
{
	g_exit_status = 127 + sig;
}
