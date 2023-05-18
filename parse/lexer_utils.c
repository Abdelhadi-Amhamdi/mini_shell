/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/18 21:40:30 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>'|| c == '&' || c == '*')
		return (1);
	return (0);
}

int	is_container(char c)
{
	if (c == '\'' || c == '"' || c == ')' || c == '(')
		return (1);
	return (0);
}

int check_op_next(char *str, int i)
{
	if ((is_operator(str[i]) && str[i + 1] != ' ') \
	&& !is_container(str[i + 1]) && !is_operator(str[i + 1]))
		return (1);
	return (0);
}

int check_op_prev(char *str, int i)
{
	if ((is_operator(str[i]) && str[i - 1] != ' ') \
	&& !is_container(str[i - 1]) && !is_operator(str[i - 1]))
		return (1);
	return (0);
}

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
