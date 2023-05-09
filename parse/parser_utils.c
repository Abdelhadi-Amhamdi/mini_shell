/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:24 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/08 17:03:25 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_file(char *str)
{
	if (!ft_strncmp((str + (ft_strlen(str) - 4)), ".txt", 4))
		return (1);
	return (0);
}

t_type	check_type(t_lexer *lexer_item, char *p)
{
	if (p)
		return (CMD);
	else if (lexer_item->str[0] == '\'')
		return (SQ);
	else if (lexer_item->str[0] == '"')
		return (DQ);
	else if (lexer_item->is_token)
		return (TOKEN);
	else if (lexer_item->str[0] == '-')
		return (ARGS);
	else if (is_file(lexer_item->str))
		return (FL);
	else if (lexer_item->str[0] == '$' && lexer_item->prev && lexer_item->prev->str[0] != '\'')
		return (VAR);
	return (UNK);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "pwd", 3)
		|| !ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5) || !ft_strncmp(cmd, "exit", 4)
		|| !ft_strncmp(cmd, "env", 3))
		return (1);
	return (0);
}

void	print_parser_list(t_parser *list)
{
	while (list)
	{
		printf("string : %s\n", list->str);
		printf("path : %s\n", list->path);
		printf("is_builtin : %s\n", list->is_builtin ? "true" : "false");
		printf("type : %s\n",
				(list->type == 0) ? "CMD" : ((list->type == 1)) ? "UNK"
																				: ((list->type == 2) ? "TOKEN" : ((list->type == 3) ? "ARGS" : ((list->type == 4) ? "VAR" : ((list->type == 5) ? "FILE" : "Q")))));
		printf("----------\n");
		list = list->next;
	}
}
