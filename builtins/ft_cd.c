/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:21:50 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/08 14:56:31 by aagouzou         ###   ########.fr       */
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

void	ft_cd(t_env *env, t_parser *path)
{
	t_env	*home;
	t_env	*oldpwd;
	t_env	*pwd;

	home = ft_search_env(env, "HOME");
	oldpwd = ft_search_env(env, "OLDPWD");
	pwd = ft_search_env(env, "PWD");
	oldpwd->value = getcwd(NULL, 0);
	if (!home || !oldpwd)
		return ;
	if (!path)
		chdir(home->value);
	else
	{
		if (path->str[0] == '~')
			path->str = update_path(path->str + 1, home->value);
		if (chdir(path->str) == -1)
			perror("cd");
	}
	pwd->value = getcwd(NULL, 0);
}
