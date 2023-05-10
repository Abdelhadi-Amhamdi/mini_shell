/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:52:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/10 10:44:10 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_free_lexer_list(t_lexer *list)
{
	t_lexer	*tmp;
	t_lexer	*next;

	tmp = list;
	while (tmp)
	{
		next = tmp->next;
		free (tmp);
		tmp = next;
	}
}

t_parser	*formater(char *cmd, t_env *envp)
{
	t_lexer		*lexer_list;
	t_parser	*parser_list;

	lexer_list = lexer(cmd);
	// print_token_list(lexer_list);
	parser_list = parser(lexer_list, envp);
	// print_parser_list(parser_list);
	ft_free_lexer_list(lexer_list);
	ft_expander(parser_list, envp);
	return (parser_list);
}
