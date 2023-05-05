/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:21:50 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/05 15:12:21 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


//function to edit env variable, treat case where we unset home ,
void	ft_cd(t_list *env, const char *path)
{
	char	*p;

	// check if no path or the path absolute
	if (!path || !ft_strncmp(path, "~", 1))
	{
		// get the home path and switch to it
		p = ft_search_env(env , "HOME=");
		if (!p)
			return ;
		chdir(p + 5);
		if (!path)
		{ // if not path change the curent working directory in env and return .
			ft_unset("PWD=", &env);
			p = ft_strjoin("PWD=", getcwd(NULL, 0));
			ft_export(p, env);
			return ;
		}
	}
	// skip the ~ and / characters
	while (*path && *path == '~')
		path++;
	if (*path)
	{ // change the directory if the path not NULL 
		if (chdir(path) == -1)
		{	
			// change derictory to the given 
			// path and print error if path not exist
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putendl_fd((char *)path, 2);
		}
	}
	// if not path change the curent working directory in env .
	ft_unset("PWD=", &env);
	p = ft_strjoin("PWD=", getcwd(NULL, 0));
	ft_export(p, env);
}
