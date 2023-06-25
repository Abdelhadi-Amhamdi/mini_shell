/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:41:30 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/25 16:38:53 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	_free_lexer(t_lexer **list)
{
	t_lexer	*tmp;
	t_lexer	*next;

	tmp = *list;
	if (!tmp)
		return ;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == HEREDOC_FILE)
			unlink(tmp->str);
		del_node(tmp);
		tmp = next;
	}
	*list = NULL;
}

void	del_p_node(t_parser *node, int t)
{
	if (!node)
		return ;
	if (t && node->args_list)
		_free_lexer(&node->args_list);
	node->args_list = NULL;
	free(node->str);
	node->str = NULL;
	if (node->path)
		free(node->path);
	node->path = NULL;
	free(node);
	node = NULL;
}

void	_free_parser(t_parser **list, int t)
{
	t_parser	*tmp;
	t_parser	*next;

	tmp = *list;
	while (tmp)
	{
		next = tmp->next;
		del_p_node(tmp, t);
		tmp = next;
	}
	*list = NULL;
}
