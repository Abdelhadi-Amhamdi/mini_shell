/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:50:24 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/20 23:05:05 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

//free 2D array
void	ft_free(char **tabs)
{
	int	index;

	index = 0;
	if (!tabs || !*tabs)
		return ;
	while (tabs[index])
	{
		free(tabs[index]);
		index++;
	}
	free(tabs);
	tabs = NULL;
}

//remove a node
void	del_node(t_lexer *node)
{
	if (!node)
		return ;
	free(node->str);
	node->str = NULL;
	if (node->path)
		free(node->path);
	node->path = NULL;
	free(node);
	node = NULL;
}

//remove space before operatore
void	remove_prev_space(t_lexer *tmp, t_lexer **list)
{
	t_lexer	*cur;
	t_lexer	*space;

	cur = tmp->prev->prev;
	space = tmp->prev;
	if (cur)
	{
		cur->next = tmp;
		tmp->prev = cur;
		del_node(space);
	}
	else
	{
		*list = tmp;
		tmp->prev = NULL;
		del_node(space);
	}
}

void	remove_next_space(t_lexer *tmp, t_lexer **list)
{
	t_lexer	*cur;
	t_lexer	*space;

	(void)list;
	cur = tmp->next->next;
	space = tmp->next;
	tmp->next = cur;
	if (cur)
		cur->prev = tmp;
	del_node(space);
}

//clean white space between operators
void	clean_spaces(t_lexer **list)
{
	t_lexer	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->is_oper && tmp->prev && tmp->prev->type == W_SPACE && tmp->prev->id != PREINTABLE_SPACE)
			remove_prev_space(tmp, list);
		if (tmp->is_oper && tmp->next && tmp->next->type == W_SPACE && tmp->next->id != PREINTABLE_SPACE)
			remove_next_space(tmp, list);
		tmp = tmp->next;
	}
}
