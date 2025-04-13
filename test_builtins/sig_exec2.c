#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_sigtest
{
	char	*s;
	struct sigaction	sa;
	int	fdin;
	struct s_sigtest	*next;
}	t_sigtest;

sig_atomic_t	g_sig_exit;

void	handle_sigint(int sig)
{
	g_sig_exit = sig;
}

void	signal_setup(struct sigaction *sa, sigset_t *mask, int child)
{
	sigemptyset(mask);
	sigaddset(mask, SIGINT);
	if (child)
		sa->sa_handler = handle_sigint;
	else
		sa->sa_handler = SIG_IGN;
	sa->sa_mask = *mask;
	sigaction(SIGINT, sa, NULL);
}

int	child_proc(t_sigtest *data)
{
	data->s = calloc(11, 1);
	data->fdin = open("text", O_RDONLY);
	if (data->fdin != -1)
		sleep(100);
	close(data->fdin);
	free(data->s);
	free(data);
	if (g_sig_exit)
		exit (128 + g_sig_exit);
	exit (0);
}

int	main(void)
{
	pid_t			pid;
	sigset_t		mask;
	int			status;
	int	excode;
	t_sigtest	*data;

	g_sig_exit = 0;
	excode = 0;
	data = calloc(1, sizeof(t_sigtest));

	signal_setup(&(data->sa), &mask, 0);
	pid = fork();
	if (pid)
	{
		waitpid(pid, &status, 0);
		printf("WIFEXITED: %d\n", WIFEXITED(status));
		printf("WIFSIGNALED: %d\n", WIFSIGNALED(status));
	//	if (WIFSIGNALED(status))
	//		excode = 128 + WTERMSIG(status);
	//	else
			excode = status >> 8;
	}
	else
	{
		signal_setup(&(data->sa), &mask, 1);
		child_proc(data);
	}
	free(data->s);
	free(data);
	return (excode);
}
