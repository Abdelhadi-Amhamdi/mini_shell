/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:43:05 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/26 12:03:06 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_tree	*create_node(t_parser *item)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->str = ft_strdup(item->str);
	new_node->type = item->type;
	new_node->is_builtin = item->is_builtin;
	if (item->path)
		new_node->path = ft_strdup(item->path);
	else
		new_node->path = NULL;
	new_node->cmd_args = item->args_list;
	new_node->is_op = false;
	new_node->args = NULL;
	new_node->id = item->id;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_tree	*create_token_node(t_parser *node, t_tree *left, t_tree *right)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->str = ft_strdup(node->str);
	new_node->type = node->type;
	new_node->cmd_args = NULL;
	new_node->is_op = true;
	new_node->id = node->id;
	new_node->left = left;
	new_node->right = right;
	new_node->is_builtin = false;
	return (new_node);
}

t_tree	*create_tree(t_parser **list)
{
	t_tree		*res;
	t_parser	*op;
	t_tree		*right;

	res = termx(list);
	while ((*list) && (*list)->is_op && (!ft_strncmp((*list)->str, "&&", 3)
			|| !ft_strncmp((*list)->str, "||", 3)))
	{
		op = (*list);
		(*list) = (*list)->next;
		right = termx(list);
		res = create_token_node(op, res, right);
	}
	return (res);
}

t_tree	*termx(t_parser **list)
{
	t_tree		*res;
	t_parser	*op;
	t_tree		*right;

	res = term(list);
	while ((*list) && (*list)->is_op && !ft_strncmp((*list)->str, "|", 2))
	{
		op = (*list);
		(*list) = (*list)->next;
		right = term(list);
		res = create_token_node(op, res, right);
	}
	return (res);
}

t_tree	*term(t_parser **list)
{
	t_tree		*res;
	t_parser	*op;
	t_tree		*right;

	res = factor(list);
	while ((*list) && (*list)->is_op && (ft_strncmp((*list)->str, "&&", 3)
			&& ft_strncmp((*list)->str, "||", 3) && ft_strncmp((*list)->str,
				"|", 2)))
	{
		op = (*list);
		(*list) = (*list)->next;
		right = factor(list);
		res = create_token_node(op, res, right);
		if (!res->left)
			break ;
	}
	if (res && !res->left && res->is_op && (res->type == APND || res->type \
	== RDIR) && *list && (*list)->type != CP)
		res->left = term(list);
	return (res);
}
