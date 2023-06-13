/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:25:44 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/13 19:10:11 by aamhamdi         ###   ########.fr       */
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

int	ft_pwd(t_env	*envp, int out)
{
	char	*path;

	path = getcwd(NULL, 0);
	if(path)
		ft_putendl_fd(path, out);
	else
		ft_putendl_fd(get_cwd(envp), out);
	return (0);
}
	