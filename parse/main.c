/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:52:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/05 13:18:51 by aamhamdi         ###   ########.fr       */
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
	ft_expander(parser_list, envp);
	print_parser_list(parser_list);
	return (0);
}