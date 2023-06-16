/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 23:32:37 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/16 23:34:15 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_pipes	*pipe_node_create(int **pipe)
{
	t_pipes	*p;

	p = malloc(sizeof(t_pipes));
	if (!p)
		return (NULL);
	p->pipe = *pipe;
	p->next = NULL;
	return (p);
}

void	add_to_end(t_pipes **list, t_pipes *item)
{
	t_pipes	*tmp;

	if (!(*list))
		*list = item;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = item;
	}
}

int	_args_size(t_lexer *list, int is_b)
{
	int	size;

	size = 0;
	while (list && is_b)
	{
		list = list->next;
		size++;
	}
	while (list && !is_b)
	{
		if (list->type != W_SPACE)
			size++;
		list = list->next;
	}
	return (size);
}

int	path_exist(char *path, char **paths)
{
	int	index;

	index = 0;
	while (paths[index])
	{
		if (!ft_strncmp(path, paths[index], ft_strlen(paths[index])))
			return (1);
		index++;
	}
	return (0);
}
