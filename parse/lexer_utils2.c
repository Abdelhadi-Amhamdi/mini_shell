/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:45:53 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/28 15:54:39 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	compare(t_lexer	*item, char *oper)
{
	return (ft_strncmp(item->str, oper, ft_strlen(item->str)));
}

int	is_special_char(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')' || c == '*')
		return (1);
	return (0);
}

int	is_container(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	check_op_next(char *str, int i)
{
	if ((is_special_char(str[i]) && str[i + 1] != ' ') \
	&& (str[i] != str[i + 1] || !is_operator(str[i + 1])))
		return (1);
	return (0);
}

int	check_op_prev(char *str, int i)
{
	if ((is_special_char(str[i]) && str[i - 1] != ' ') \
	&& (str[i] != str[i - 1] || !is_operator(str[i - 1])))
		return (1);
	return (0);
}

int is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}
