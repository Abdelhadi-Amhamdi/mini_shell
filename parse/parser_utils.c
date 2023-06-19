/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:28:44 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/17 21:52:49 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// printf("is_op  : %s\n", list->is_op ? "true" : "false");
void	print_parser_list(t_parser *list)
{
	while (list)
	{
		printf("string : [%s]\n", list->str);
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
