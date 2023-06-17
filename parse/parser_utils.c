/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:28:44 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/16 15:51:16 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_parser_list(t_parser *list)
{
	while (list)
	{
		printf("string : [%s]\n", list->str);
		printf("is_op  : %s\n", list->is_op ? "true" : "false");
		printf("ID     : %d\n", list->id);
		while (list->args_list)
		{
			printf("          : [%s]\n", list->args_list->str);
			list->args_list = list->args_list->next;
		}
		printf("type   : %d\n", list->type);
		printf("----------\n");
		list = list->next;
	}
}
