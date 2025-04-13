/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiepark <jiepark@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:29:39 by jiepark           #+#    #+#             */
/*   Updated: 2025/04/03 20:55:07 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "builtins.h"

typedef struct s_env t_env;

# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2
# define NO_QUOTE 0
# define BLANK_IN_QUOTE -1

//envvar_expander.c
char	*ev_expander(t_mshell *data, char *line);
// utils
int		count_linelen(t_list *lst);
char	*set_next_p(char *line);
int	check_dol_questn(char *key, char **envval, int excode);

//wildcard_expander.c
char	**wc_expander(t_mshell *data, char *line);
// utils
int		filter_line(char *s, char *fil);
void	rm_lstnode(t_list **lst, t_list *node);
int		count_lstnode(t_list *lst);

//test + expander
void	testprint_env(t_env *env);
void	testprint_lst(t_list *lst);

//handle_qot_envvar
void	handle_qot_envvar(t_mshell *ms, t_ast *node);

//util_check_qot
int		surrounded_by_single_quotes(char *arg);
int		has_quotes(char *arg);
int		has_nested_quotes(char *arg);
int		get_outer_quote_type(const char *str);
int		needs_processing(const char *arg);

//char *get_env_var(t_mshell *ms, char *key_part);

char *extract_key(char *key_part);
t_env *find_env_var(t_env *env, char *key);
#endif
