/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:30:36 by ********          #+#    #+#             */
/*   Updated: 2025/04/02 20:49:35 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	ms_cd(t_env *env, char **args)
{
	char	*home;
	char	*fullpath;
	int		n;

	n = count_args(args);
	if (n > 2)
		return (err_msg(ERR_EXIT_ARG, "cd"), 1);
	if (n == 2 && access(args[1], F_OK | X_OK))
		return (errno_msg("cd", args[1]), 1);
	set_env_val(env, "OLDPWD", get_working_dir(env));
	if (n == 1)
	{
		home = get_env_val(env, "HOME");
		if (chdir(home))
			return (ERR);
		set_env_val(env, "PWD", home);
	}
	else
	{
		fullpath = get_fullpath(args[1]);
		if (!fullpath || chdir(args[1]))
			return (ERR);
		set_env_val(env, "PWD", fullpath);
	}
	return (0);
}
