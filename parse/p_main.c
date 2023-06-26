/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:52:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/26 08:42:12 by aamhamdi         ###   ########.fr       */
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

void	ft_p_error(char *str, t_tree *tmp, int status)
{
	ft_putstr_fd("min-sh: ", 2);
	ft_putstr_fd(tmp->str, 2);
	ft_putendl_fd(str, 2);
	if (status >= 0)
		g_exit_status = status;
	else if (status == -1)
		tmp->id = status;
}

void	p_error(char *str, t_lexer *tmp, int status)
{
	ft_putstr_fd("min-sh: ", 2);
	ft_putstr_fd(tmp->str, 2);
	ft_putendl_fd(str, 2);
	if (status >= 0)
		g_exit_status = status;
	else if (status == -1)
		tmp->id = status;
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
	tmp = NULL;
	lexer_list = lexer(cmd, data->env);
	if (!lexer_list)
		return (NULL);
	if (ft_expander(&lexer_list, data->env))
		return (_free_lexer(&lexer_list), NULL);
	parser_list = parser(lexer_list, data);
	if (!parser_list)
		return (_free_lexer(&lexer_list), NULL);
	_free_lexer(&lexer_list);
	tmp = parser_list;
	ast_tree = create_tree(&tmp);
	_free_parser(&parser_list, 0);
	return (ast_tree);
}
