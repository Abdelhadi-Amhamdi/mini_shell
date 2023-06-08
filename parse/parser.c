/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/08 22:15:19 by aamhamdi         ###   ########.fr       */
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
	new_node->id = node->id;
	new_node->path = ft_strdup(node->path);
	new_node->str = ft_strdup(node->str);
	new_node->type = node->type;
	return (new_node);
}

t_lexer *handle_rdir_case(t_parser **parser_list, t_lexer *arg, t_lexer **args_list)
{
	add_node_to_list(parser_list, create_parser_node(arg, 1));
	arg = arg->next;
	add_node_to_list(parser_list, create_parser_node(arg, 1));
	arg = arg->next;
	while (arg && !arg->is_oper)
	{
		add_token_to_end(args_list, ft_nodedup(arg));
		arg = arg->next;
	}
	return (arg);
}

t_parser *create_blocks(t_lexer *lexer_list)
{
	t_parser *parser_list;
	t_lexer *args_list;
	t_lexer *tmp;
	t_lexer *first_arg;
	t_parser *new_node;
	
	tmp = lexer_list;
	parser_list = NULL;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			new_node = create_parser_node(tmp, 1);
			add_node_to_list(&parser_list, new_node);
			first_arg = tmp->next;
			args_list = NULL;
			if (first_arg && (first_arg->type == RDIR || first_arg->type == APND))
			{
				tmp = handle_rdir_case(&parser_list, first_arg, &args_list);
				new_node->args_list = args_list;
			}
			else
			{
				while (first_arg && !first_arg->is_oper)
				{
					add_token_to_end(&args_list, ft_nodedup(first_arg));
					first_arg = first_arg->next;
				}
				new_node->args_list = args_list;
				tmp = first_arg;
			}
		}
		else
		{
			new_node = create_parser_node(tmp, 1);
			add_node_to_list(&parser_list, new_node);
			tmp = tmp->next;
		}
	}
	return (parser_list);
}

t_parser	*parser(t_lexer *lexer_list)
{
	t_parser	*parser_list;

	parser_list = create_blocks(lexer_list);
	if (!parser_list)
		return (NULL);
	return (parser_list);
}
