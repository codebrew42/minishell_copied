/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:51:38 by ********          #+#    #+#             */
/*   Updated: 2025/04/01 11:15:17 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define ERR -1

# include "builtins.h"
# include "heredoc.h"

typedef enum e_op
{
	OP_NONE,
	OP_OR,
	OP_AND,
	OP_PIPE
}	t_op;

typedef enum e_bltin
{
	BI_NONE,
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT
}	t_bltin;

typedef enum e_type		t_type;
typedef struct s_mshell	t_mshell;

typedef struct s_cmd
{
	char			*path;
	char			**args;
	t_bltin			bi;
	t_op			op;
	t_type			type_rdct[2];
	char			*file_path[2];
	int				fdin;
	int				fdout;
	int				pipe[2];
	int				paren[2];
	int				*pipe_prev[2];
	int				*pids;
	int				child;
	struct s_cmd	*next;
}		t_cmd;

// executor.c
int		executor(t_mshell *data);
int		exec_cmds(t_mshell *data, t_cmd *cmds, int *pids);
int		create_subshell(t_mshell *data, t_cmd *cmds, t_cmd **tmp, int *pids);
int		create_cmdproc(t_mshell *data, t_cmd **cmd, t_cmd *cmd_root, int *pids);
void	wait_cmdproc(t_mshell *data, int *pids);

// exec_init.c
int		init_executor(t_mshell *data, t_cmd **cmds, int **pids);
void	set_cmddata(t_ast *ast, t_cmd *cmds, t_heredoc *hdc);
void	set_rdct_type(t_ast *ast, t_cmd *cmd, t_type type, t_heredoc *hdc);
void	set_paren_status(t_cmd *cmd);

// exec_stream.c
int		open_file(t_cmd *cmd);
int		create_pipe(t_cmd *cmd);
void	close_pstream(t_cmd *cmd);

// exec_cmdproc.c
int		cmd_proc(t_mshell *data, t_cmd *cmd, t_cmd *cmd_root);
int		set_cstream(t_cmd *cmd);
int		check_cmd(t_mshell *data, t_cmd *cmd, t_cmd *cmd_root);
//void	excute_builtin(t_mshell *data, t_cmd *cmd, t_builtin bi);
char	*create_pathstr(char *path, char *cmd);

// exec_builtin.c
int		exec_builtin(t_mshell *data, t_cmd *cmd, t_cmd *cmd_root);
int		call_builtin(t_mshell *data, t_cmd *cmd, t_cmd *cmd_root, int *std);
void	exit_exec(t_mshell *data, t_cmd *cmd);
t_bltin	isbuiltin(char *s);

// exec_utils.c
int		count_cmd(t_ast *ast);
int		op_check(t_cmd **cmd, int exit);
void	free_cmdproc(t_mshell *data, t_cmd *cmd_root);
void	free_cmddata(t_cmd *cmd);
void	err_cmd(t_mshell *data, t_cmd *cmd_root, char *cmd);

//utils2
int		set_stdinout(int from, int to);
int		count_cmdlst(t_cmd *cmd);
int		check_paren(t_ast *ast);
int		check_paren_syntx(t_ast *ast, int open, int close);
int		check_paren_with_op(t_ast *ast);
void	moveto_parenend(t_cmd **cmd);

//test_exec.c
void	testprint_cmds(t_cmd *cmd);

#endif
