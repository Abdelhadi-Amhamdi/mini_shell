/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:57:36 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/17 11:18:45 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_path(char *cmd, char **paths)
{
	char	*command;
	char	*full_path;
	int		index;

	command = ft_strjoin("/", cmd);
	index = 0;
	if (!command)
		return (NULL);
	while (paths[index])
	{
		full_path = ft_strjoin(paths[index], command);
		if (!full_path)
			return (free(command), NULL);
		if (!access(full_path, F_OK | X_OK))
			return (free(command), full_path);
		free(full_path);
		index++;
	}
	free(command);
	return (NULL);
}

int	is_var(t_lexer *node)
{
	int	s_count;
	int	d_count;

	s_count = 0;
	d_count = 0;
	while (node)
	{
		if (node->is_oper && node->str[0] == '\'')
			s_count++;
		if (node->is_oper && node->str[0] == '"')
			d_count++;
		node = node->prev;
	}
	if ((s_count % 2) && !(d_count % 2))
		return (0);
	return (1);
}

int	ft_char_search(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

int	ft_last_char_search(char *str, char c)
{
	int	index;

	index = ft_strlen(str) - 1;
	while (index >= 0)
	{
		if (str[index] == c)
			return (index);
		index--;
	}
	return (-1);
}

int	is_wild_card(t_lexer *node)
{
	if (node->str[0] != '"' && node->str[0] != '\'' && \
		ft_char_search(node->str, '*') != -1)
		return (1);
	return (0);
}
