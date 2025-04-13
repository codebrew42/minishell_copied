/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_execve_wait.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:53:55 by ********          #+#    #+#             */
/*   Updated: 2025/02/14 18:57:55 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	err_exit(void);

int	main(int ac, char **av, char **envp)
{
	pid_t	n;
	char 	*args[2] = {"ls", NULL};

	n = fork();
	if (n == -1)
		err_exit();
	if (!n)
	{
		if (execve("/bin/ls", args, envp))
			err_exit();
	}
	else
	{
		write(1, "parent\n", 7);
		wait(NULL);
	}
	exit(0);
}

void	err_exit(void)
{
	perror("Error");
	exit(1);
}
