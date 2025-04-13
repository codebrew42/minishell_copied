/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:16:06 by ********          #+#    #+#             */
/*   Updated: 2025/04/01 11:18:00 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "expander.h"

# define HDC_FILE "/tmp/minishell_hd"

typedef struct s_heredoc
{
	char				*filename;
	char				**lim;
	int					fd;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_mshell	t_mshell;

void	ms_heredoc(t_mshell *data);
int		init_heredoc(t_mshell *data);
//heredoc_utils.c
int		create_hdc_file(t_heredoc *hdc);
void	clean_hdc(t_mshell *data);

// from exec_utils2.c
int		set_stdinout(int from, int to);

#endif
