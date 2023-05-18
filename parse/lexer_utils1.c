/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:57:36 by aagouzou          #+#    #+#             */
/*   Updated: 2023/05/18 21:46:01 by aamhamdi         ###   ########.fr       */
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

int	is_file(char *str)
{
	if (!ft_strncmp((str + (ft_strlen(str) - 4)), ".txt", 4))
		return (1);
	return (0);
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

t_type	check_type(t_lexer *lexer_item, char *path)
{
	if (path || is_builtin(lexer_item->str))
		return (CMD);
	else if (lexer_item->str[0] == '\'')
		return (SQ);
	else if (lexer_item->str[0] == '"')
		return (DQ);
	else if (lexer_item->str[0] == '(')
		return (OP);
	else if (lexer_item->str[0] == ')')
		return (CP);
	else if (lexer_item->is_oper && !compare(lexer_item, "|"))
		return (PIPE);
	else if (lexer_item->is_oper && !compare(lexer_item, ">"))
		return (RDIR);
	else if (lexer_item->is_oper && !compare(lexer_item, ">>"))
		return (APND);
	else if (lexer_item->str[0] == '-')
		return (ARGS);
	else if (is_file(lexer_item->str))
		return (FL);
	else if (lexer_item->str[0] == '$' && is_var(lexer_item->prev))
		return (VAR);
	return (UNK);
}