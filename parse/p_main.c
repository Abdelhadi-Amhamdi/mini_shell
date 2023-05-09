/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:52:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/08 18:54:06 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_parser	*formater(char *cmd, t_env *envp)
{
	t_lexer		*lexer_list;
	t_parser	*parser_list;

	lexer_list = lexer(cmd);
	// print_token_list(lexer_list);
	parser_list = parser(lexer_list, envp);
	// print_parser_list(parser_list);
	ft_expander(parser_list, envp);
	return (parser_list);
}
