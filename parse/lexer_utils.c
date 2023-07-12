/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/12 08:59:17 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	add_middle_node(t_lexer *new, t_lexer *prev, t_lexer *next,
		t_lexer *last)
{
	prev->next = new;
	new->prev = prev;
	last->next = next;
	if (next)
		next->prev = last;
}


void print_lexer(t_lexer *list)
{
	t_lexer *tmp;
	// t_lexer *args;

	tmp = list;
	while (tmp)
	{
		printf("str :[%s]\n", tmp->str);
		tmp = tmp->next;
	}
	
}