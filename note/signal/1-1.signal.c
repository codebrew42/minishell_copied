/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:28:05 by ********          #+#    #+#             */
/*   Updated: 2025/02/14 14:30:14 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	handle_tstp(int sig)
{
	printf("signal: %d\nstop not allowed.\n", sig);
}

int	main(void)
{
	pid_t			pid;
	struct sigaction 	sa;

	sa.sa_handler = &handle_tstp;
	sigaction(SIGTSTP, &sa, NULL);

	pid = fork();
	if (pid)
	{
		//kill(pid, SIGKILL);
		//kill(pid, SIGSTOP);
		kill(pid, SIGTSTP);
		sleep(1);
		kill(pid, SIGCONT);
		//wait(NULL);
	}
	else
	{
		puts("child process");
	}
}
