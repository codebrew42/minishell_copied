/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:49:43 by ********          #+#    #+#             */
/*   Updated: 2025/03/16 12:39:52 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int	main(void)
{
	DIR	*dirp = NULL;
	struct dirent	*dirent;

	dirp = opendir("/home/miya/work/minishell/test_builtins");
	if (!dirp)
		return (1);
	while (1)
	{
		dirent = NULL;
		dirent = readdir(dirp);
		if (!dirent)
			break ;
		printf("index num of file: %ld\n", dirent->d_ino);
		printf("type of file: %c\n", dirent->d_type);
		printf("name: %s\n\n", dirent->d_name);
		//free(dirent); no need
	}
	closedir(dirp);
	return (0);
}
