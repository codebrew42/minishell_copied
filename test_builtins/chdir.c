/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 21:10:06 by ********          #+#    #+#             */
/*   Updated: 2025/04/02 14:09:08 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	printf("pwd: %s\n", pwd);
	free(pwd);
	if (chdir("testlink"))
		perror("error");
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	printf("pwd: %s\n", pwd);
	free(pwd);
}
