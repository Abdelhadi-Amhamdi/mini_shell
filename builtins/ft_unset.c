/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:54:35 by aagouzou          #+#    #+#             */
/*   Updated: 2023/05/15 14:18:37 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/mini_shell.h"

t_env	*env_search(t_parser	*node, t_env	*env)
{
	while(env)
	{
		if(!ft_strncmp(node->str, env->key, ft_strlen(node->str) + 1))
			return(env);
		env = env->next;
	}
	return (NULL);
}

t_env	*ft_unset(t_parser	*node, t_env *env)
{
	t_env	*cur;
	t_env	*prev;
	
	if(!node)
		return env;
	
	cur = env_search(node, env);
	if(!cur)
		return env;
	prev = cur->prev;
	if(!prev)
	{
		env = cur->next;
		env->prev = NULL;
		free(cur);
		return (env);
	}
	prev->next = cur->next;
	free(cur);
	return (env);
}
