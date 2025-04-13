/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:51:10 by ********          #+#    #+#             */
/*   Updated: 2025/04/02 20:43:03 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	count_args(char **args)
{
	int	n;

	n = 0;
	while (args[n])
		n++;
	return (n);
}

int	is_symlink(char *cwd, char *link)
{
	struct stat	st_c;
	struct stat	st_l;

	if (stat(cwd, &st_c))
		return (ERR);
	if (stat(link, &st_l))
		return (ERR);
	if (st_c.st_ino == st_l.st_ino)
		return (1);
	return (0);
}

char	*get_fullpath(char *path)
{
	char	*fullp;
	char	*cwd;

	if (path[0] == '/')
		fullp = ft_strdup(path);
	else if (*path && !ft_strncmp(path, ".", 2))
		fullp = getcwd(NULL, 0);
	else if (ft_strlen(path) == 2 && !ft_strncmp(path, "..", 3))
	{
		fullp = getcwd(NULL, 0);
		cwd = ft_strrchr(fullp, '/');
		if (cwd)
			*cwd = 0;
	}
	else
		fullp = create_fullp(path);
	return (fullp);
}

char	*create_fullp(char *file)
{
	char	*fullp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	fullp = ft_strjoin(cwd, "/");
	if (!fullp)
		return (NULL);
	free(cwd);
	cwd = fullp;
	fullp = ft_strjoin(cwd, file);
	free(cwd);
	return (fullp);
}
