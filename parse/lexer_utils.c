/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/26 12:09:20 by aagouzou         ###   ########.fr       */
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
