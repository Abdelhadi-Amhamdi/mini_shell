/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/16 18:36:08 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_parser	*create_parser_node(t_lexer *l_node, int id)
{
	t_parser	*new_node;

	new_node = malloc(sizeof(t_parser));
	if (!new_node)
		return (NULL);
	new_node->args_list = NULL;
	new_node->is_op = l_node->is_oper;
	new_node->is_builtin = l_node->is_builtin;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->id = id;
	new_node->path = ft_strdup(l_node->path);
	new_node->str = ft_strdup(l_node->str);
	new_node->type = l_node->type;
	return (new_node);
}

void	add_node_to_list(t_parser **list, t_parser *item)
{
	t_parser	*tmp;

	tmp = *list;
	if (!*list)
		*list = item;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = item;
		item->prev = tmp;
	}
}

t_lexer	*ft_nodedup(t_lexer *node)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->is_builtin = node->is_builtin;
	// new_node->is_oper = node->is_builtin;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->id = node->id;
	new_node->path = ft_strdup(node->path);
	new_node->str = ft_strdup(node->str);
	new_node->type = node->type;
	return (new_node);
}

t_parser	*parser(t_lexer *lexer_list, t_main *data)
{
	t_parser	*parser_list;

	parser_list = create_blocks(lexer_list, data);
	if (!parser_list)
		return (NULL);
	return (parser_list);
}
