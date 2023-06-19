/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:47:30 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/19 11:47:55 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_lexer	*_create_doc(char *data, t_type type)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->str = ft_strdup(data);
	new_node->type = type;
	new_node->path = NULL;
	new_node->id = 0;
	new_node->is_builtin = 0;
	new_node->is_oper = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}


void	_add_doc_to_end(t_lexer **head, t_lexer *new_item)
{
	t_lexer	*current;

	current = *head;
	if (!current)
		*head = new_item;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_item;
		new_item->prev = current;
	}
}