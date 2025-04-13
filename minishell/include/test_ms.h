#ifndef TEST_MS_H
# define TEST_MS_H

typedef struct	s_ast t_ast;
typedef struct	s_cmd t_cmd;
typedef enum	e_type t_type;

//test_utils.c
void	lst_add_ast(t_ast **ast, t_type t, char *argstr);
void	set_ast(t_ast **ast, t_type t, char ***args);
int	find_print_env(t_env *env, char *name);
void	testprint_cmds(t_cmd *cmd);
void	testprint_ast(t_ast *ast);

//test_utils2.c
void	print_path(char **path);
void	testprint_args(char **args);
void	testprint_lst(t_list *lst);

#endif
