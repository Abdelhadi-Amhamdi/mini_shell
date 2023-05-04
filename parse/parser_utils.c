/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:24 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/04 16:37:18 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_type	check_type(t_lexer *lexer_item, char *p)
{
	if (p)
		return (CMD);
	else if (lexer_item->is_token)
		return (TOKEN);
	else if (lexer_item->str[0] == '-')
		return (ARGS);
	return (UNK);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "pwd", 3) \
	|| !ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "export", \
	6) || !ft_strncmp(cmd, "unset", 5) || !ft_strncmp(cmd, "exit", 4))
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
		printf("type : %s\n", (list->type == 0) ? "CMD" \
		: ((list->type == 1)) ? "UNK" \
		: ((list->type == 2) ? "TOKEN" : "ARGS"));
		printf("---------------------------\n");
		list = list->next;
	}
}
