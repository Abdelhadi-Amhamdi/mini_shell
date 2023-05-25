/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:44:05 by aagouzou          #+#    #+#             */
/*   Updated: 2023/05/24 17:17:11 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_env	*ft_search_env(t_env *env_list, char *to_find)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, to_find, ft_strlen(to_find)))
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

void	ft_cd(t_env *env, t_tree *path)
{
	t_env	*home;
	t_env	*oldpwd;
	t_env	*pwd;

	home = ft_search_env(env, "HOME");
	oldpwd = ft_search_env(env, "OLDPWD");
	pwd = ft_search_env(env, "PWD");
	if (!home)
		return ;
	if (!oldpwd)
	{
		oldpwd = ft_new_node("OLDPWD", getcwd(NULL, 0));
		if(oldpwd)
			ft_add_back_env(&env, oldpwd);
	}
	else
		oldpwd->value = getcwd(NULL, 0);
	if (!path->cmd_args[1])
		chdir(home->value);
	else
	{
		if (path->str[0] == '~')
			path->str = update_path(path->str + 1, home->value);
		if (chdir(path->cmd_args[1]) == -1)
			perror("cd");
	}
	pwd->value = getcwd(NULL, 0);
	
}
