/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:51:51 by jiepark           #+#    #+#             */
/*   Updated: 2025/03/17 18:51:52 by jiepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "minishell.h"

typedef struct s_mshell		t_mshell;
typedef struct s_env		t_env;

int				init_mshell(t_mshell **ms_data, char **envp);

#endif
