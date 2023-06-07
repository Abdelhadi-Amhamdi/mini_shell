/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/06 20:44:39 by aamhamdi         ###   ########.fr       */
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

t_lexer *ft_nodedup(t_lexer *node)
{
	t_lexer *new_node;

	new_node =  malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->is_builtin = node->is_builtin;
	// new_node->is_oper = node->is_builtin;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->path = NULL;
	new_node->str = ft_strdup(node->str);
	new_node->type = node->type;
	return (new_node);
}


t_parser *create_blocks(t_lexer *lexer_list)
{
	t_parser *parser_list;
	t_parser *new_node;
	t_lexer  *tmp;
	t_lexer  *next_node;
	t_lexer  *args_list;
	int index;

	tmp = lexer_list;
	parser_list = NULL;
	index = 0;
	while (tmp)
	{
		if (tmp->type == CMD && tmp->next && !tmp->next->is_oper)
		{
			new_node = create_parser_node(tmp, index);
			next_node = tmp->next;
			args_list = NULL;
			while (next_node && !next_node->is_oper && next_node->type != OP && next_node->type != CP)
			{
				add_token_to_end(&args_list, ft_nodedup(next_node));
				next_node = next_node->next;
			}
			new_node->args_list = args_list;
			tmp = next_node;
		}
		else
		{
			new_node = create_parser_node(tmp, index);
			new_node->args_list = NULL;
			tmp = tmp->next;
		}
		add_node_to_list(&parser_list, new_node);
		index++;
	}
	return (parser_list);
}

// t_parser	*create_blocks(t_lexer *lexer_list)
// {
// 	t_parser	*blocks_list;
// 	t_lexer		*tmp;
// 	t_lexer		*tmp1;
// 	t_parser	*new_node;

// 	tmp = lexer_list;
// 	blocks_list = NULL;
// 	new_node = NULL;
// 	while (tmp)
// 	{
// 		if (tmp->type == CMD)
// 		{
// 			new_node = create_parser_node(tmp);
// 			tmp1 = tmp->next;
// 			new_node->args_list = NULL;
// 			while (tmp1 && !tmp1->is_oper && tmp1->type != OP && tmp1->type != CP)
// 			{
// 				add_token_to_end(&(new_node->args_list), ft_nodedup(tmp1));
// 				tmp1 = tmp1->next;
// 			}
//             tmp = tmp1;
// 		}
// 		else
// 		{
//         	new_node = create_parser_node(tmp);
// 			tmp = tmp->next;
// 		}
//         add_node_to_list(&blocks_list, new_node);
// 	}
// 	return (blocks_list);
// }

t_parser	*parser(t_lexer *lexer_list)
{
	t_parser	*parser_list;

	parser_list = create_blocks(lexer_list);
	if (!parser_list)
		return (NULL);
	return (parser_list);
}
