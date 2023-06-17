/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:18:22 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/17 11:42:24 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_env	*ft_new_node(char *key, char *val)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = val;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	ft_add_back_env(t_env **list, t_env *item)
{
	t_env	*tmp;

	tmp = *list;
	if (!(*list))
		*list = item;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = item;
		item->prev = tmp;
	}
}

int	env_list_size(t_env *list)
{
	int	index;

	index = 0;
	while (list)
	{
		index++;
		list = list->next;
	}
	return (index);
}

int	ft_search(char *item, char tofind)
{
	int	index;

	index = 0;
	while (item[index])
	{
		if (item[index] == tofind)
			return (index);
		index++;
	}
	return (-1);
}
