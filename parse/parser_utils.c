/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:28:44 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/21 11:08:44 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// printf("is_op  : %s\n", list->is_op ? "true" : "false");
void	print_parser_list(t_parser *list)
{
	t_lexer *tmp_args;
	t_parser *tmp;

	tmp = list;
	while (tmp)
	{
		tmp_args = tmp->args_list;
		printf("string : [%s]\n", tmp->str);
		printf("ID     : %d\n", tmp->id);
		while (tmp_args)
		{
			printf("          : [%s]\n", tmp_args->str);
			tmp_args = tmp_args->next;
		}
		printf("type   : %d\n", tmp->type);
		printf("----------\n");
		tmp = tmp->next;
	}
}
