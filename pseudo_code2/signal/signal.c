/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:49:35 by ********          #+#    #+#             */
/*   Updated: 2025/02/15 17:53:15 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	handle_signal()
{
	struct sigaction sa1;
	struct sigaction sa2;

	sa1.sa_handler = &handle_sigint;
	sa2.sa_handler = &handle_sigquit;
	sigaction(SIGINT, &sa1, NULL);
	sigaction(SIGQUIT, &sa2, NULL);
}

// behavior of ctrl + c
void	handle_sigint(int sig)
{
	//handle history
	//redisplay?
	//show prompt
}

// behavior of ctrl + '\'
void	handle_sigquit(int sig)
{
}
