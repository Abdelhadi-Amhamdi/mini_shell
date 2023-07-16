/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:54:35 by aagouzou          #+#    #+#             */
/*   Updated: 2023/07/15 15:39:37 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_env	*env_search(char *arg, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(arg, tmp->key, ft_strlen(arg) + 1))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	del_env_node(t_env *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

t_env	*ft_unset(t_tree *node, t_env *env)
{
	int		i;
	t_env	*cur;
	t_env	*prev;

	i = -1;
	if (!node)
		return (env);
	while (node->args[++i])
	{
		cur = env_search(node->args[i], env);
		if (cur)
		{
			prev = cur->prev;
			if (!prev)
			{
				env = cur->next;
				env->prev = NULL;
			}
			else
			{
				prev->next = cur->next;
				if (cur->next)
					cur->next->prev = prev;
			}
			del_env_node(cur);
		}
	}
	return (env);
}
		// i++;
