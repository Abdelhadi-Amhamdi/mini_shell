/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:54:35 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/10 20:38:55 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/mini_shell.h"

t_env	*env_search(char *arg, t_env	*env)
{
	while(env)
	{
		if(!ft_strncmp(arg, env->key, ft_strlen(arg) + 1))
			return(env);
		env = env->next;
	}
	return (NULL);
}

t_env	*ft_unset(t_tree	*node, t_env *env)
{
	int i = 0;
	t_env	*cur;
	t_env	*prev;
	
	if(!node)
		return env;
	while(node->args[i])
	{
		cur = env_search(node->args[i], env);
		if(cur)
		{
			prev = cur->prev;
			if(!prev)
			{
				env = cur->next;
				env->prev = NULL;
			}
			else
				prev->next = cur->next;
			free(cur);
		}
		i++;
	}
	return (env);
}
