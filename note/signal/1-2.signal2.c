/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:28:05 by ********          #+#    #+#             */
/*   Updated: 2025/02/14 14:49:00 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	handle_tstp(int sig)
{
	printf("signal: %d\nstop not allowed.\n", sig);
	sleep(5);
}

//How to block a signal while the process act for an other signal.
int	main(void)
{
	pid_t			pid;
	struct sigaction 	sa;
	sigset_t		mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGTERM);

	sa.sa_handler = &handle_tstp;
	sa.sa_mask = mask;
	sigaction(SIGTSTP, &sa, NULL);

	pid = fork();
	if (pid)
	{
		kill(pid, SIGTSTP);
		sleep(1);
		kill(pid, SIGTERM);
		sleep(1);
		kill(pid, SIGCONT);
	}
	else
		puts("child process");
}
