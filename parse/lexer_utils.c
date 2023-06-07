/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/07 18:08:04 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_token_list(t_lexer *head)
{
	t_lexer	*cur;

	cur = head;
	while (cur != NULL)
	{
		printf("STR : [%s]\n", cur->str);
		printf("IS_B: [%u]\n",cur->is_builtin);
		printf("IS_O: [%s]\n", cur->is_oper ? "true" : "false");
		printf("ID: [%d]\n", cur->id);
		if(cur->type == 7)
			printf("TYPE: VAR\n");
		else
			printf("TYPE: [%u]\n",cur->type);
		printf("PATH: [%s]\n",cur->path);
		// while ()
		// printf("is_|bu|iltin	: %s\n",cur->is_builtin ? "true" : "false");
		// printf("type : %s\n", (cur->type == 0) ? "CMD" : (cur->type == 1) ? "PIPE" \
		//  : (cur->type == 2) ? "RDIR" : (cur->type == 3) ? "APND" : (cur->type == 4) ? "AND" : (cur->type == 5) ? "OR" : (cur->type == 6) ? "ARGS" : (cur->type == 7) ? "VAR": (cur->type == 8) ? "FILE": (cur->type == 9) ? "SQ": (cur->type == 10) ? "DQ"\
		//  : (cur->type == 11) ? "OP": ((cur->type == 12) ? "CP": (cur->type == 15) ? "wildcard" : "UNK"));
		// printf("type index %u\n",cur->type);
		cur = cur->next;
		puts("------------------------------");
	}
}
