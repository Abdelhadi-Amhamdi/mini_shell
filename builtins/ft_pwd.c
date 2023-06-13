/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:25:44 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/11 18:10:35 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char *get_cwd(t_env	*envp)
{
	t_env	*tmp;

	tmp = envp;
	while(tmp)
	{
		if(!ft_strncmp(tmp->key,"PWD",3))
			break;
		tmp = tmp->next;
	}
	return(tmp->value);
}

int	ft_pwd(t_env	*envp)
{
	char	*path;

	path = getcwd(NULL, 0);
	if(path)
		ft_putendl_fd(path, 1);
	else
		ft_putendl_fd(get_cwd(envp),1);
	return (0);
}
	