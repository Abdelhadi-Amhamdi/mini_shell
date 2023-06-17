/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:41:30 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/16 15:52:32 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_free_lexer_list(t_lexer **list)
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

void	del_p_node(t_parser *node)
{
	if (!node)
		return ;
	node->args_list = NULL;
	free(node->str);
	node->str = NULL;
	if (node->path)
		free(node->path);
	node->path = NULL;
	free(node);
	node = NULL;
}

void	ft_free_parser_list(t_parser **list)
{
	t_parser	*tmp;
	t_parser	*next;

	tmp = *list;
	while (tmp)
	{
		next = tmp->next;
		del_p_node(tmp);
		tmp = next;
	}
	*list = NULL;
}
