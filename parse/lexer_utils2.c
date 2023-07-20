/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:45:53 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/19 20:45:15 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int	is_special_char(char c)
// {
// 	if (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')'
// 		|| c == '*')
// 		return (1);
// 	return (0);
// }

// int	is_container(char c)
// {
// 	if (c == '\'' || c == '"')
// 		return (1);
// 	return (0);
// }

// int	check_op_next(char *str, int i)
// {
// 	if ((is_special_char(str[i]) && str[i + 1] != ' ') && (str[i] != str[i + 1]
// 			|| !is_operator(str[i + 1])))
// 		return (1);
// 	return (0);
// }

// int	check_op_prev(char *str, int i)
// {
// 	if ((is_special_char(str[i]) && str[i - 1] != ' ') && (str[i] != str[i - 1]
// 			|| !is_operator(str[i - 1])))
// 		return (1);
// 	return (0);
// }

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}
