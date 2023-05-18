/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/18 21:48:20 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*check_args(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_op_next(str, i))
			return (str);
		if (check_op_prev(str, i))
			return (str);
		i++;
	}
	return (NULL);
}

size_t	count_new_args_size(char *str)
{
	size_t	count;
	int		index;

	count = 0;
	index = 0;
	while (str[index])
	{
		if (check_op_next(str, index))
			count++;
		if (check_op_prev(str, index))
			count++;
		index++;
		count++;
	}
	return (count);
}

char	*filter_args_helper(char *str)
{
	size_t	size;
	char	*new_str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	size = count_new_args_size(str);
	new_str = malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	while (str[++i])
	{
		if (check_op_prev(str, i))
			new_str[j++] = ' ';
		new_str[j++] = str[i];
		if (check_op_next(str, i))
			new_str[j++] = ' ';
	}
	new_str[j] = '\0';
	return (new_str);
}

char	**args_filter(char *str)
{
	char	*args;
	char	**tabs;

	args = NULL;
	args = check_args(str);
	if (args)
		args = filter_args_helper(args);
	else
		args = ft_strdup(str);
	tabs = ft_split(args, ' ');
	free(args);
	if (!tabs)
		return (NULL);
	return (tabs);
}

void	print_token_list(t_lexer *head)
{
	t_lexer	*cur;

	cur = head;
	while (cur != NULL)
	{
		printf("String: :%s:\n", cur->str);
		// printf("Is token: %s\n", cur->is_oper ? "true" : "false");
		// printf("path	: %s\n",cur->path);
		// printf("is_builtin	: %s\n",cur->is_builtin ? "true" : "false");
		printf("type : %s\n", (cur->type == 0) ? "CMD" : (cur->type == 1) ? "PIPE" \
		 : (cur->type == 2) ? "RDIR" : (cur->type == 3) ? "APND" : (cur->type == 4) ? "AND" : (cur->type == 5) ? "OR" : (cur->type == 6) ? "ARGS" : (cur->type == 7) ? "VAR": (cur->type == 8) ? "FILE": (cur->type == 9) ? "SQ": (cur->type == 10) ? "DQ": (cur->type == 11) ? "OP": ((cur->type == 12) ? "CP": "UNK"));
		// printf("type index %u\n",cur->type);
		printf("-------------------------\n");
		cur = cur->next;
	}
}
