/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:28:44 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/27 11:33:42 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"



void	print_parser_list(t_parser *list)

{
	while (list)
	{
		printf("string : %s\n", list->str);
		// printf("is_builtin : %s\n", list->is_builtin ? "true" : "false");
		while (list->args_list)
		{
			printf("     %s\n", list->args_list->str);
			list->args_list = list->args_list->next;
		}
		printf("type : %d\n", list->type);
		// printf("type : %s\n", (list->type == 0) ? "CMD" \
		// : ((list->type == 1)) ? "UNK": ((list->type == 2) ? "TOKEN" : ((list->type == 3) ? "ARGS" \
		// : ((list->type == 4) ? "VAR" : ((list->type == 8) ? "FILE" : "Q")))));
		printf("----------\n");
		list = list->next;
	}
}
