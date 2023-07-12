/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:33:29 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/12 16:15:10 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_tree	*factor(t_parser **list)
{
	t_tree	*res;

	res = NULL;
	if ((*list)->type == OP)
	{
		(*list) = (*list)->next;
		res = create_tree(list);
		(*list) = (*list)->next;
	}
	else if ((*list) && !(*list)->is_op)
	{
		res = create_node(*list);
		(*list) = (*list)->next;
	}
	return (res);
}
