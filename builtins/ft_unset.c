/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:54:35 by aagouzou          #+#    #+#             */
/*   Updated: 2023/07/22 09:11:10 by aagouzou         ###   ########.fr       */
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
	while (node && node->args[++i])
	{
		if (!check_key(node->args[i]))
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
					prev->next = cur->next;
				if (cur->next && prev)
					cur->next->prev = prev;
				del_env_node(cur);
			}
		}
		else
			ft_putendl_fd("unset: not a valid identifier", 2);
	}
	return (env);
}
