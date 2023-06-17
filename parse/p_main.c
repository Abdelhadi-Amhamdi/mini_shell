/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:52:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/17 13:15:44 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	ft_tabs_len(char **tabs)
{
	int	index;

	index = 0;
	while (tabs[index])
		index++;
	return (index);
}

int	ft_error(char *str)
{
	return (printf("%s `%s'!\n", SYNTAX_ERROR_MSG, str));
}

t_tree	*formater(char *cmd, t_main *data)
{
	t_parser	*tmp;
	t_lexer		*lexer_list;
	t_parser	*parser_list;
	t_tree		*ast_tree;

	lexer_list = NULL;
	parser_list = NULL;
	ast_tree = NULL;
	lexer_list = lexer(cmd, data->env);
	if (!lexer_list)
		return (NULL);
	if (ft_expander(lexer_list, data->env))
		return (ft_free_lexer_list(&lexer_list), NULL);
	parser_list = parser(lexer_list, data);
	if (!parser_list)
		return (ft_free_lexer_list(&lexer_list), NULL);
	ft_free_lexer_list(&lexer_list);
	tmp = parser_list;
	ast_tree = create_tree(&tmp);
	ft_free_parser_list(&parser_list);
	return (ast_tree);
}
