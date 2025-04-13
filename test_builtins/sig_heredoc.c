#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

sig_atomic_t	g_sig_exit;

void	handle_sigint(int sig)
{
	g_sig_exit = sig + 128;
	write(1, "\n", 1);
//	rl_done = 1;
	close(0);
}

void	signal_setup(struct sigaction *sa, sigset_t *mask)
{
	sigemptyset(mask);
	sigaddset(mask, SIGINT);
	sa->sa_handler = handle_sigint;
	sa->sa_mask = *mask;
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
}

int	main(void)
{
	char	*input;
	struct sigaction	sa;
	sigset_t		mask;
	int			status;

	g_sig_exit = 0;
	signal_setup(&sa, &mask);
	while (1)
	{
		input = readline("test> ");
		if (!input)
			break ;
	}
	
}
