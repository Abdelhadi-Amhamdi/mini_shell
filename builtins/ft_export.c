/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:23:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/15 13:29:50 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export(char *new_variable, t_list *env)
{
	t_list	*node;
	t_list	*last;

	if (!env)
		return ;
	// creat new node with the givendata
	node = ft_lstnew(new_variable);
	if (!node)
		return ;
	// add it to the list
	last = ft_lstlast(env);
	last->next = node;
}
