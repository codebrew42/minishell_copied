/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:56:03 by ********          #+#    #+#             */
/*   Updated: 2025/02/14 17:13:08 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;

	while(1)
	{
		input = readline(">> ");
		if (!input) //break if ctrl + D
			break ;
		puts(input);
		free(input); //still memory leak, but the subject says ok...
	}
	return (0);
}

