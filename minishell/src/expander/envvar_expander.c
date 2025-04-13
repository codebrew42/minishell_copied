/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:22:35 by ********          #+#    #+#             */
/*   Updated: 2025/04/03 20:55:20 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

static void	create_exp_lst(t_mshell *data, t_list **lst, char *line);
static char	*create_new_line(t_list *lst);
static void	parse_line(t_mshell *data, t_list *lst, char *line, char *top);
static char	*get_env_var(t_env *env, char *line, char *end, int excode);

char	*ev_expander(t_mshell *data, char *line)
{
	t_list	*lst;
	char	*new;

	if (!line || !*line)
		return (line);
	if (!strncmp(line, "$", 2) || !ft_strchr(line, '$'))
		return (line);
	create_exp_lst(data, &lst, line);
	new = create_new_line(lst);
	ft_lstclear(&lst, &free);
	free(line);
	return (new);
}

static void	create_exp_lst(t_mshell *data, t_list **lst, char *line)
{
	*lst = ft_lstnew(NULL);
	if (!lst)
		err_exit(NULL, 0);
	parse_line(data, *lst, line, line);
	//testprint_lst(*lst);//to remove
}

static void	parse_line(t_mshell *data, t_list *lst, char *line, char *top)
{
	char	*next;
	char	*sub;

	if (!top || !lst)
		return ;
	next = set_next_p(top);
	if (next && *top == '$')
		sub = get_env_var(data->env_var, top, next - 1, data->dol_questn);
	else if (next && *next == '$')
		sub = ft_substr(top, 0, next - top);
	else
		sub = ft_strdup(top);
	if (!sub)
		err_exit(NULL, 0);
	lst->content = (void *)sub;
	if (!*next)
		lst->next = NULL;
	else
	{
		lst->next = ft_lstnew((void *)sub);
		if (!lst->next)
			err_exit(NULL, 0);
	}
	parse_line(data, lst->next, line, next);
}

static char	*get_env_var(t_env *env, char *line, char *end, int excode)
{
	char	*key;
	char	*envval;
	t_env	*node;

	envval = NULL;
	node = NULL;
	line++;
	key = ft_substr(line, 0, end - line + 1);
	if (!key)
		return (NULL);
	if (check_dol_questn(key, &envval, excode))
		return (free(key), NULL);
	if (envval)
		return (free(key), envval);
	node = search_env_name(env, key);
	if (node)
	{
		envval = ft_strdup(node->value);
		if (!envval)
			return (free(key), NULL);
	}
	if (!envval)
		envval = ft_strdup("");
	free(key);
	return (envval);
}

static char	*create_new_line(t_list *lst)
{
	int		new_len;
	char	*new;
	char	*tmp;
	char	*sub;

	new_len = count_linelen(lst);
	new = ft_calloc(new_len + 1, 1);
	tmp = new;
	while (lst)
	{
		sub = ((char *)lst->content);
		ft_strlcat(tmp, sub, new_len + 1);
		lst = lst->next;
		tmp += ft_strlen(tmp);
	}
	return (new);
}
