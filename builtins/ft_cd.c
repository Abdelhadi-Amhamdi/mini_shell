/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:44:05 by aagouzou          #+#    #+#             */
/*   Updated: 2023/07/22 10:14:08 by aagouzou         ###   ########.fr       */
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

int	ft_cd_helper(t_env *home, t_tree	*path, t_main *data)
{
	char	*ret;
	char	*tmp;

	if (path->args[0][0] == '~' && home)
		path->args[0] = update_path(&path->args[0][1], home->value);
	if (chdir(path->args[0]) == -1)
		return (perror("cd"), 1);
	ret = getcwd(NULL, 0);
	if (ret)
	{
		tmp = data->cwd;
		data->cwd = ret;
		free(tmp);
	}
	else
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory", 2);
		tmp = data->cwd;
		data->cwd = ft_strjoin(data->cwd, "/..");
		free(tmp);
	}
	return (0);
}

int	ft_cd(t_env *env, t_tree *path, t_main *data)
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
	{
		if (chdir(home->value) == -1)
			return (perror("cd"), 1);
	}
	else if (!path->args[0] && !home)
		return (ft_putendl_fd("mini-sh: cd: HOME not set", 2), 1);
	else
	{
		if (ft_cd_helper(home, path, data) == 1)
			return (1);
	}
	if (pwd)
		change_old_value(pwd);
	return (0);
}
