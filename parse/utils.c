/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/04 11:59:08 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

char	*check_args(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_token(str[i]) && ((str[i - 1] != ' ' \
		&& !is_token(str[i - 1])) || (str[i + 1] \
		!= ' ' && !is_token(str[i + 1]) && str[i + 1] != '\0')))
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
		if (is_token(str[index]) && str[index + 1] != ' ' \
		&& !is_token(str[index + 1]))
			count++;
		if (is_token(str[index]) && str[index - 1] != ' ' \
		&& !is_token(str[index - 1]))
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
		if (is_token(str[i]) && str[i - 1] != ' ' && !is_token(str[i - 1]))
			new_str[j++] = ' ';
		new_str[j++] = str[i];
		if (is_token(str[i]) && str[i + 1] != ' ' && !is_token(str[i + 1]))
			new_str[j++] = ' ';
	}
	new_str[j] = '\0';
	return (new_str);
}

char	**args_filter(char *str)
{
	char	*args;
	char	**tabs;

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
