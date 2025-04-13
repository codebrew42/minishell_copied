#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	errno = 0;
	access("/usr/bin/ls", F_OK);
	perror("Minishell");
	access("/usr/ls", F_OK);
	perror("Minishell");
	

	return (0);
}
