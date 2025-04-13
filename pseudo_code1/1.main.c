#include "minishell.h"


int	print_err(int flag, char *s)
{
	if (!flag)
		printf("Error: %s\n", s);
	if (flag == 1)
		perror("malloc");
	else if (flag == 2)
		perror("read");
	else if (flag == 3)
		perror("add_history");
	return (1);
}

/**
 * malloc: t_shell, t_token, t_ast, t_env
  free: shell will be freed in main
 **/
int	init_shell(t_shell **s)
{
	*s = malloc(sizeof(t_shell));
	if (!*s)
		return (print_err(1, NULL));
	(*s)->tokens = NULL;
	(*s)->ast_root = NULL;
	(*s)->env_array = NULL;
	(*s)->exit_requested = 0;
	(*s)->exit_status = 0;
	// Initialize environment (?)
	if (!init_environment(*s, envp))
	{
		free(*s);
		return (print_err(0, "Environment initialization failed"));
	}
	return (0);
}

char *read_line(void)
{
	char *line;
	
	line = readline("minishell$ ");
	if (!line)
		return (NULL);  // Handle EOF (Ctrl+D)
	return (line);
}

void setup_signal_handlers(void)
{
	signal(SIGINT, handle_sigint);    // Ctrl+C
	signal(SIGQUIT, SIG_IGN);         // Ctrl+backslash
}

void minishell(t_shell *s, char **envp)
{
	char *line;
	int status;
	
	setup_signal_handlers();
	
	while (!s->exit_requested)
	{
		status = 0;
		line = read_line();
		if (!line)  //EOF (Ctrl+D)
			break;
		// Skip empty lines
		if (*line == '\0')
		{
			free(line);
			continue; //check
		}
		add_history(line);
		if (tokenize_input(s, line))
		{
			printf("Tokenization error\n");
			free(line);
			continue; //check
		}
		if (parse(s))
		{
			printf("Parsing error\n");
			free_tokens(s->tokens);
			s->tokens = NULL;
			free(line);
			continue; //check
		}
		make_heredoc(s);
		execute(s);
		s->exit_status = get_execution_status(s);
		// Free temp resources
		free_tokens(s->tokens);
		s->tokens = NULL;
		free_ast(s->ast_root);
		s->ast_root = NULL;
		free(line);
	}
}

int main(int ac, char **av, char **envp)
{
	t_shell *s;
	int exit_status;
	
	if (init_shell(&s, envp))
		return (1);
	minishell(s, envp);
	exit_status = s->exit_status; //before cleanup
	free_shell(s);
	return (exit_status);
}
