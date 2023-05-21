/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/21 16:09:56 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"



t_parser	*create_parser_node(t_lexer *l_node)
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
    new_node->str = l_node->str;
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

t_lexer *ft_nodedup(t_lexer *node)
{
	t_lexer *new_node;

	new_node =  malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->is_builtin = node->is_builtin;
	new_node->is_oper = node->is_builtin;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->path = node->path;
	new_node->str = node->str;
	new_node->type = node->type;
	return (new_node);
}


t_parser	*create_blocks(t_lexer *lexer_list)
{
	t_parser	*blocks_list;
	t_lexer		*tmp;
	t_lexer		*tmp1;
	t_parser	*new_node;

	tmp = lexer_list;
	blocks_list = NULL;
	new_node = NULL;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			new_node = create_parser_node(tmp);
			tmp1 = tmp->next;
			while (tmp1 && !tmp1->is_oper)
			{
				add_token_to_end(&(new_node->args_list), ft_nodedup(tmp1));
				tmp1 = tmp1->next;
			}
            tmp = tmp1;
		}
		else
		{
        	new_node = create_parser_node(tmp);
			new_node->args_list = NULL;
			tmp = tmp->next;
		}
        add_node_to_list(&blocks_list, new_node);
	}
	return (blocks_list);
}

t_parser	*parser(t_lexer *lexer_list)
{
	t_parser	*parser_list;

	parser_list = create_blocks(lexer_list);
	if (!parser_list)
		return (NULL);
	return (parser_list);
}
