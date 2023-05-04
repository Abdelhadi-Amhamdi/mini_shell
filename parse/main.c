/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:52:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/04 16:16:31 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int ac, char **av, char **envp)
{
	t_lexer		*lexer_list;
	t_parser	*parser_list;

	if (ac < 2)
		return (0);
	lexer_list = lexer(av[1]);
	parser_list = parser(lexer_list, envp);
	while (parser_list)
	{
		printf("string : %s\n", parser_list->str);
		printf("path : %s\n", parser_list->path);
		printf("is_builtin : %s\n", parser_list->is_builtin ? "true" : "false");
		printf("type : %s\n", (parser_list->type == 0) ? "CMD" : ((parser_list->type == 1)) ? "UNK" : ((parser_list->type == 2)? "TOKEN" : "ARGS"));
		printf("---------------------------\n");
		parser_list = parser_list->next;
	}
	return (0);
}