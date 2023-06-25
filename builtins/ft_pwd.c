/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:25:44 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/24 20:37:51 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*get_cwd(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 3))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return(NULL);
}

int	ft_pwd(t_env *envp, int out)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_putendl_fd(path, out);
		free(path);
	}
	else
	{
		path = get_cwd(envp);
		if(path)
		{
			ft_putendl_fd(path, out);
			free(path);
		}
	}
	return (0);
}
