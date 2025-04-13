/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <********@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:29:51 by ********          #+#    #+#             */
/*   Updated: 2025/03/25 10:49:04 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

static int	get_file_lst(t_list **lst);
static int	create_filelst(t_list **lst, DIR *dirp);
static void	filter_lst(t_list **lst, t_list *tmp, char *filter);
static int	create_filename_array(char ***new_files, t_list *lst);

char	**wc_expander(t_mshell *data, char *line)
{
	t_list	*lst;
	char	**new_files;

	if (!line || !*line || !ft_strchr(line, '*'))
		return (NULL);
	lst = NULL;
	new_files = NULL;
	if (get_file_lst(&lst) == ERR)
		return (free_mshell(data), err_exit(NULL, 0), NULL);
	//testprint_lst(lst);//test
	if (!lst)
		return (NULL);
	filter_lst(&lst, lst, line);
	//testprint_lst(lst);//test
	create_filename_array(&new_files, lst);
	return (new_files);
}

static int	get_file_lst(t_list **lst)
{
	char	*pwd;
	DIR		*dirp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ERR);
	dirp = NULL;
	dirp = opendir(pwd);
	if (!dirp)
		return (ERR);
	if (create_filelst(lst, dirp) == ERR)
		return (ERR);
	closedir(dirp);
	free(pwd);
	return (0);
}

static int	create_filelst(t_list **lst, DIR *dirp)
{
	struct dirent	*dirent;
	t_list			*new;
	char			*fname;

	errno = 0;
	while (1)
	{
		dirent = readdir(dirp);
		if (!dirent && errno)
			return (ERR);
		else if (!dirent)
			break ;
		if (!strncmp(dirent->d_name, ".", 2) || \
			!strncmp(dirent->d_name, "..", 3))
			continue ;
		fname = ft_strdup(dirent->d_name);
		if (!fname)
			return (ERR);
		new = ft_lstnew((void *)fname);
		if (!new)
			return (ERR);
		ft_lstadd_back(lst, new);
	}
	return (0);
}

static void	filter_lst(t_list **lst, t_list *tmp, char *filter)
{
	if (!tmp->next && *lst == tmp)
	{
		if (!filter_line((char *)tmp->content, filter))
			rm_lstnode(lst, tmp);
		return ;
	}
	else if (!tmp->next)
		return ;
	filter_lst(lst, tmp->next, filter);
	if (!filter_line((char *)tmp->next->content, filter))
		rm_lstnode(lst, tmp->next);
	if (tmp == *lst)
	{
		if (!filter_line((char *)tmp->content, filter))
			rm_lstnode(lst, tmp);
	}
}

static int	create_filename_array(char ***new_files, t_list *lst)
{
	char	**new;
	t_list	*tmp;
	int		n;

	n = count_lstnode(lst);
	if (!n)
	{
		*new_files = NULL;
		return (0);
	}
	*new_files = ft_calloc(n + 1, sizeof(char *));
	if (!*new_files)
		return (ERR);
	new = *new_files;
	while (n--)
	{
		*new = (char *)lst->content;
		tmp = lst;
		lst = lst ->next;
		free(tmp);
		new++;
	}
	*new = NULL;
	return (0);
}
