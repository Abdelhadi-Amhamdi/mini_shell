/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:21:50 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/06 16:41:01 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"


t_env	*ft_search_env(t_env *env_list, char *to_find)
{
	t_env *tmp;

	tmp = env_list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, to_find, ft_strlen(to_find)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_cd(t_env *env, t_parser *path)
{
	t_env	*p;

	if (!path || !ft_strncmp(path->str, "~", 1))
	{
		p = ft_search_env(env , "HOME");
		if (!p)
			return ;
		chdir(p->value);
		if (!path)
		{
			p->value = getcwd(NULL, 0);
			return ;
		}
	}
	// while (*path && *path == '~')
	// 	path++;
	else if (path)
	{
		if (chdir(path->str) == -1)
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putendl_fd(path->str, 2);
		}
	}
	p = ft_search_env(env, "PWD");
	p->value = getcwd(NULL, 0);
}
