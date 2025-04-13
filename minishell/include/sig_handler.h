/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:53:58 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/31 14:50:05 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_HANDLER_H
# define SIG_HANDLER_H
# include "minishell.h"

# define SIGNAL_MODE_INTERACTIVE 0
# define SIGNAL_MODE_CHILD 1
# define SIGNAL_MODE_HEREDOC 2
# define SIGNAL_MODE_PARENT_WAITING 3

# ifdef __APPLE__

extern void		rl_replace_line(const char *text, int clear_undo);
extern void		rl_clear_history(void);
extern int		rl_on_new_line(void);
extern void		rl_redisplay(void);
# endif

void			setup_signals(int mode);
void			execution_signal_handler(int sig_nbr);
void			interactive_sigint_handler(int sig);
void			heredoc_sigint_handler(int sig);
void			cmdproc_signal_handler(int sig);

//signal_util.c
void			set_terminal_print_off(void);
void			set_terminal_print_on(void);
#endif
