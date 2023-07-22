/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:25:44 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/22 09:10:54 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*get_cwd(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD1", 4))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_pwd(t_env *envp, int out, t_main *data)
{
	char	*path;

	(void)envp;
	path = getcwd(NULL, 0);
	if (path)
	{
		ft_putendl_fd(path, out);
		free(path);
	}
	else if (errno == ENOENT)
	{
		ft_putendl_fd(data->cwd, out);
	}
	return (0);
}
