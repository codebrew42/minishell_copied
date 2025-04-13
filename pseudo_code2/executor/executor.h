/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:51:38 by ********          #+#    #+#             */
/*   Updated: 2025/03/01 19:29:22 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCUTOR_H
# define EXCUTOR_H

# incldue "minishell.h"

# define HERED_PATH "minishell_heredoc"

typedef enum 	e_op
{
	OP_NONE,
	OP_AND,
	OP_OR
}	t_op;

typedef enum	e_builtin
{
	BI_NONE,
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPT,
	BI_UNSET,
	BI_EXIT
}	t_builtin;

typedef enum e_redirect
{
	RD_NONE,
	RD_IN,
	RD_HD,
	RD_OUT,
	RD_APP,
	RD_PIPE;
}	t_redirect;

typedef struct	s_cmd
{
	char	*path;
	char	**args;
	int		fdin;
	int		fdout;
	t_redirect	type_rdct[2];
	char	*file_path[2];
	int		pipe[2];
	int		*to_close[2];
	t_op	op;
	struct s_cmd	*next;
}	t_cmd;

// executor.c
void	executor(t_data *data);
int	init_excutor(t_mshell *data, t_cmd **cmds, int **pids);
void	set_cmddata(t_ast *ast, t_cmd *cmds);

// exec_parent.c
void	create_cmdproc(t_data *data, t_cmd **cmd, int *pids);
void	open_file(t_cmd *cmd);
void	wait_cmdproc(t_data *data);

// exec_cmdproc.c
int	cmd_proc(t_data *data, t_cmd *cmd);
void	set_stream(t_cmd *cmd);
void	check_cmd(t_cmd *cmd, char **path);
void	excute_buildin(t_data *data, t_cmd *cmd, t_buildin bi);

// exec_utils.c
int	count_cmd(t_ast *ast);
t_buildin	isbuildin(char *s);
void	free_exec(t_cmd *cmds);

#endif
