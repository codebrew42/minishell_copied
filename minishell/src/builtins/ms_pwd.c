/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:54:57 by ********          #+#    #+#             */
/*   Updated: 2025/04/02 20:47:50 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	ms_pwd(t_env *env)
{
	char	*pwd;

	pwd = get_working_dir(env);
	if (!pwd)
		return (ERR);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

//check if symb. link: compare result of getcwd and $PWD
char	*get_working_dir(t_env *env)
{
	char	*cwd;
	char	*env_pwd;
	int		islink;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	env_pwd = get_env_val(env, "PWD");
	if (strncmp(env_pwd, cwd, ft_strlen(cwd) + 1))
	{
		islink = is_symlink(cwd, env_pwd);
		if (islink == ERR)
			return (NULL);
		else if (islink)
			return (free(cwd), ft_strdup(env_pwd));
	}
	return (cwd);
}
