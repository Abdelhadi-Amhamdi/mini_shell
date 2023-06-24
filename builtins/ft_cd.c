/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:44:05 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/24 10:53:13 by aagouzou         ###   ########.fr       */
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
	path = ft_strjoin(path, str);
	return (path);
}

void	change_old_value(t_env *node)
{
	char	*old;
	char	*new;

	old = node->value;
	new = getcwd(NULL, 0);
		node->value = ft_strdup(new);
	free(old);
	free(new);
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
		change_old_value(oldpwd);
	if (!path->args[0] && home)
		chdir(home->value);
	else if (!path->args[0] && !home)
		return (ft_putendl_fd("mini-sh: cd: HOME not set", 2), 1);
	else
	{
		if (path->args[0][0] == '~')
			path->args[0] = update_path(&path->args[0][1], home->value);
		if (chdir(path->args[0]) == -1)
			return (perror("cd"), 1);
	}
	if (pwd)
		change_old_value(pwd);
	return (0);
}
