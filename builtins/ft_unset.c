/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:54:35 by aagouzou          #+#    #+#             */
/*   Updated: 2023/07/22 10:35:08 by aamhamdi         ###   ########.fr       */
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

void	ft_unset_helper(t_tree *node, t_env *env, int *i)
{
	t_env	*cur;
	t_env	*prev;

	cur = env_search(node->args[*i], env);
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

int	ft_unset(t_tree *node, t_env *env)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (node && node->args[++i])
	{
		if (!check_key(node->args[i]))
			ft_unset_helper(node, env, &i);
		else
		{
			ft_putendl_fd("unset: not a valid identifier", 2);
			status = 1;
		}
	}
	return (status);
}
