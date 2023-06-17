/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:44:05 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/16 11:24:14 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_env	*ft_search_env(t_env *env_list, char *to_find)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, to_find, ft_strlen(tmp->key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*update_path(char *str, char *path)
{
	ft_strlcat(path, str, (ft_strlen(str) + ft_strlen(path) + 1));
	return (path);
}

int	ft_cd(t_env *env, t_tree *path)
{
	t_env	*home;
	t_env	*oldpwd;
	t_env	*pwd;

	home = ft_search_env(env, "HOME");
	oldpwd = ft_search_env(env, "OLDPWD");
	pwd = ft_search_env(env, "PWD");
	if (oldpwd)
		oldpwd->value = getcwd(NULL, 0);
	if (!path->args[0] && home)
		chdir(home->value);
	else if (!path->args[0] && !home)
		return (ft_putendl_fd("mini-sh: cd: HOME not set", 2), 1);
	else
	{
		if (path->str[0] == '~')
			path->str = update_path(path->str + 1, home->value);
		if (chdir(path->args[0]) == -1)
			return (perror("cd"), -1);
	}
	if (pwd)
		pwd->value = getcwd(NULL, 0);
	return (0);
}
